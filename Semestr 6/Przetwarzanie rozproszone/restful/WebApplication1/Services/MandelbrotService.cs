using System;
using System.IO;
using System.Threading.Tasks;
using System.Numerics;
using System.Drawing;
using System.Drawing.Imaging;

namespace WcfService1.services
{
    public class MandelbrotService
    {
        public string GenerateMandelbrot(int width, int height, int threadCount)
        {
            Bitmap bitmap = new Bitmap(width, height);
            Random rng = new Random();

            Color[] threadColors = new Color[threadCount];
            for (int i = 0; i < threadCount; i++)
            {
                threadColors[i] = Color.FromArgb(255, rng.Next(256), rng.Next(256), rng.Next(256));
            }

            int rowsPerThread = height / threadCount;
            Parallel.For(0, threadCount, threadIndex =>
            {
                int yStart = threadIndex * rowsPerThread;
                int yEnd = (threadIndex == threadCount - 1) ? height : yStart + rowsPerThread;
                Color background = threadColors[threadIndex];

                for (int y = yStart; y < yEnd; y++)
                {
                    for (int x = 0; x < width; x++)
                    {
                        double a = (x - width / 2.0) * 4.0 / width;
                        double b = (y - height / 2.0) * 4.0 / height;

                        Complex c = new Complex(a, b);
                        Complex z = Complex.Zero;
                        int iterations = 0;
                        const int maxIterations = 1000;

                        while (iterations < maxIterations && z.Magnitude <= 2)
                        {
                            z = z * z + c;
                            iterations++;
                        }

                        Color pixelColor;
                        if (iterations == maxIterations)
                        {
                            pixelColor = Color.Black;
                        }
                        else
                        {
                            pixelColor = background;
                        }

                        lock (bitmap)
                        {
                            bitmap.SetPixel(x, y, pixelColor);
                        }
                    }
                }
            });

            string dir = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "mandelbrot");
            Directory.CreateDirectory(dir);

            string filename = $"mandelbrot_{DateTime.Now:yyyyMMdd_HHmmss}.png";
            string fullPath = Path.Combine(dir, filename);
            bitmap.Save(fullPath, ImageFormat.Png);

            return filename;
        }

        public byte[] GetMandelbrotFragment(string filename, int x1, int y1, int x2, int y2)
        {
            string dir = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "mandelbrot");
            string fullPath = Path.Combine(dir, filename);

            if (!File.Exists(fullPath))
                throw new FileNotFoundException("Mandelbrot file not found.");

            using (var original = new Bitmap(fullPath))
            {
                x1 = Math.Max(0, x1);
                y1 = Math.Max(0, y1);
                x2 = Math.Min(original.Width, x2);
                y2 = Math.Min(original.Height, y2);

                int width = x2 - x1;
                int height = y2 - y1;

                if (width <= 0 || height <= 0)
                    throw new ArgumentException("Invalid crop rectangle.");

                var fragment = new Bitmap(width, height);
                using (Graphics g = Graphics.FromImage(fragment))
                {
                    g.DrawImage(original, new Rectangle(0, 0, width, height), new Rectangle(x1, y1, width, height), GraphicsUnit.Pixel);
                }

                using (var ms = new MemoryStream())
                {
                    fragment.Save(ms, ImageFormat.Png);
                    return ms.ToArray();
                }
            }
        }
    }
}