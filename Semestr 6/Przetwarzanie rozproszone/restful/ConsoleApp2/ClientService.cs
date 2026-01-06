using ConsoleApp1.Models;
using System;
using System.Net.Http;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    public class ClientService
    {
        private readonly HttpClient _http;

        public ClientService()
        {
            _http = new HttpClient();
            _http.BaseAddress = new Uri("https://localhost:44350/api/");
        }

        public async Task<string> UploadMatrixChunk(MatrixChunk chunk)
        {
            var json = JsonSerializer.Serialize(chunk);
            var content = new StringContent(json, Encoding.UTF8, "application/json");

            var response = await _http.PostAsync("matrix/upload", content);
            return await response.Content.ReadAsStringAsync();
        }

        public async Task<string> MultiplyMatrices(string file1, string file2)
        {
            var response = await _http.PostAsync($"matrix/multiply?fileName1={file1}&fileName2={file2}", null);
            return await response.Content.ReadAsStringAsync();
        }

        public async Task<string> GetMatrix(string fileName)
        {
            var response = await _http.GetAsync($"matrix/{fileName}");
            return await response.Content.ReadAsStringAsync();
        }

        public async Task<string> GenerateMandelbrot(int width, int height, int threads)
        {
            var response = await _http.PostAsync($"mandelbrot/generate?width={width}&height={height}&threads={threads}", null);
            return await response.Content.ReadAsStringAsync();
        }

        public async Task<byte[]> GetMandelbrotFragment(string filename, int x1, int y1, int x2, int y2)
        {
            var response = await _http.GetAsync($"mandelbrot/fragment?filename={filename}&x1={x1}&y1={y1}&x2={x2}&y2={y2}");
            return await response.Content.ReadAsByteArrayAsync();
        }
    }
}
