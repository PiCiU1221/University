using ConsoleApp1;
using ConsoleApp1.Models;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace ConsoleApp2.Services
{
    public class MatrixUploadService
    {
        private readonly ClientService _client;

        public MatrixUploadService(ClientService client)
        {
            _client = client;
        }

        public async Task UploadMatrix(string matrixId, string filePath, int chunkCount)
        {
            string fullText = File.ReadAllText(filePath);
            List<string> chunks = SplitIntoChunks(fullText, chunkCount);

            var uploadTasks = chunks.Select(async (chunkData, i) =>
            {
                var chunk = new MatrixChunk
                {
                    MatrixId = matrixId,
                    ChunkIndex = i,
                    TotalChunks = chunks.Count,
                    ChunkData = chunkData
                };

                try
                {
                    string response = await _client.UploadMatrixChunk(chunk);
                    Console.WriteLine(response);
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Error uploading chunk {i}: {ex.Message}");
                }
            });

            await Task.WhenAll(uploadTasks);
        }

        private List<string> SplitIntoChunks(string text, int totalChunks)
        {
            var lines = text.Split(new[] { "\r\n", "\n" }, StringSplitOptions.None);
            int totalLines = lines.Length;

            int baseLinesPerChunk = totalLines / totalChunks;
            int remainder = totalLines % totalChunks;

            var chunks = new List<string>();
            int currentLine = 0;

            for (int i = 0; i < totalChunks; i++)
            {
                int linesInThisChunk = baseLinesPerChunk + (i < remainder ? 1 : 0);
                var chunkLines = new List<string>();

                for (int j = 0; j < linesInThisChunk && currentLine < totalLines; j++)
                {
                    chunkLines.Add(lines[currentLine++]);
                }

                chunks.Add(string.Join("\n", chunkLines));
            }

            return chunks;
        }
    }
}
