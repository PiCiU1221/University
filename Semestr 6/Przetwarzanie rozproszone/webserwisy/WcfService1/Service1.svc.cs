using WcfService1.services;

namespace WcfService1
{
    public class Service1 : IService1
    {
        private readonly MatrixService _matrixService;
        private readonly MandelbrotService _fractalService;

        public Service1()
        {
            _matrixService = new MatrixService();
            _fractalService = new MandelbrotService();
        }

        public string MultiplyMatrices(string fileName1, string fileName2)
        {
            return _matrixService.Multiply(fileName1, fileName2);
        }

        public string UploadMatrixChunk(MatrixChunk chunk)
        {
            return _matrixService.UploadChunk(chunk);
        }

        public string GetMatrixFromFile(string fileName)
        {
            return _matrixService.GetFromFile(fileName);
        }

        public string GenerateMandelbrot(int width, int height, int threadCount)
        {
            return _fractalService.GenerateMandelbrot(width, height, threadCount);
        }

        public byte[] GetMandelbrotFragment(string filename, int x1, int y1, int x2, int y2)
        {
            return _fractalService.GetMandelbrotFragment(filename, x1, y1, x2, y2);
        }
    }
}
