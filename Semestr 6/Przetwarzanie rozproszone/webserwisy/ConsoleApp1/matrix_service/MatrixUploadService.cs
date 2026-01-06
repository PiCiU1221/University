namespace ConsoleApp1.matrices
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Threading.Tasks;

    public class MatrixUploadService
    {
        private readonly ServiceReference1.Service1Client _client;

        public MatrixUploadService(ServiceReference1.Service1Client client)
        {
            _client = client;
        }

        public void UploadMatrix(string matrixId, string filePath, int chunkCount)
        {
            string fullText = File.ReadAllText(filePath);
            List<string> chunks = SplitIntoChunks(fullText, chunkCount);

            Parallel.For(0, chunks.Count, i =>
            {
                var client = new ServiceReference1.Service1Client();

                var chunk = new ServiceReference1.MatrixChunk
                {
                    MatrixId = matrixId,
                    ChunkIndex = i,
                    TotalChunks = chunks.Count,
                    ChunkData = chunks[i]
                };

                try
                {
                    string response = client.UploadMatrixChunk(chunk);
                    Console.WriteLine(response);
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Error uploading chunk {i}: {ex.Message}");
                }
                finally
                {
                    if (client.State != System.ServiceModel.CommunicationState.Faulted)
                    {
                        client.Close();
                    }
                    else
                    {
                        client.Abort();
                    }
                }
            });
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
