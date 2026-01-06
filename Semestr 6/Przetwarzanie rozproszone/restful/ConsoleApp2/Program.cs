using ConsoleApp2.Services;
using System;
using System.IO;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    class Program
    {
        static async Task Main(string[] args)
        {
            var _Client = new ClientService();

            // Mnożenie macierzy

            // Dodawanie macierzy
            //var uploadService = new MatrixUploadService(_Client);

            //string matrixId = DateTime.Now.ToString("yyyyMMdd_HHmmss");
            //string filePath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "matrices", "matrix1.txt");
            //int chunkCount = 50;

            //await uploadService.UploadMatrix(matrixId, filePath, chunkCount);

            // Mnożenie
            //string resultFileName = await _Client.MultiplyMatrices("matrix_20250529_124946.txt", "matrix_20250529_124946.txt");
            //Console.WriteLine($"Result matrix saved as: {resultFileName}");

            // Odbieranie macierzy
            //var matrixName = "matrix_20250529_125049.txt";
            //var matrixContent = await _Client.GetMatrix(matrixName);
            //Console.WriteLine("Matrix content:");
            //Console.WriteLine(matrixContent);

            // Mandelbrot

            // Generowanie
            //int width = 800;
            //int height = 600;
            //int threadCount = 4;
            //string filename = await _Client.GenerateMandelbrot(width, height, threadCount);
            //Console.WriteLine("Mandelbrot image saved as: " + filename);

            // Odbieranie
            string filename = "mandelbrot_20250529_125450.png";
            int x1 = 0;
            int y1 = 0;
            int x2 = 500;
            int y2 = 500;
            byte[] imageData = await _Client.GetMandelbrotFragment(filename, x1, y1, x2, y2);

            string saveDir = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "mandelbrot_fragments");
            Directory.CreateDirectory(saveDir);

            string savePath = Path.Combine(saveDir, $"fragment_{x1}_{y1}_{x2}_{y2}.png");
            File.WriteAllBytes(savePath, imageData);

            Console.WriteLine("Fragment saved to " + savePath);

            Console.ReadLine();
        }
    }
}
