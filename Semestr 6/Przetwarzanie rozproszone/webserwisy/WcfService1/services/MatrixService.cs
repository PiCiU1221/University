using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace WcfService1
{
    public class MatrixService
    {
        private static readonly Dictionary<string, SortedDictionary<int, string>> _chunks =
            new Dictionary<string, SortedDictionary<int, string>>();

        private static readonly Dictionary<string, int> _expectedParts =
            new Dictionary<string, int>();


        public string UploadChunk(MatrixChunk chunk)
        {
            lock (_chunks)
            {
                if (!_chunks.ContainsKey(chunk.MatrixId))
                {
                    _chunks[chunk.MatrixId] = new SortedDictionary<int, string>();
                    _expectedParts[chunk.MatrixId] = chunk.TotalChunks;
                }

                _chunks[chunk.MatrixId][chunk.ChunkIndex] = chunk.ChunkData;

                if (_chunks[chunk.MatrixId].Count == _expectedParts[chunk.MatrixId])
                {
                    var allContent = string.Join(Environment.NewLine,
                        _chunks[chunk.MatrixId].OrderBy(p => p.Key).Select(p => p.Value));

                    string filename = "matrix_" + DateTime.Now.ToString("yyyyMMdd_HHmmss") + ".txt";
                    string dir = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "matrices");
                    Directory.CreateDirectory(dir);
                    string path = Path.Combine(dir, filename);
                    File.WriteAllText(path, allContent);

                    _chunks.Remove(chunk.MatrixId);
                    _expectedParts.Remove(chunk.MatrixId);

                    return "Matrix assembled and saved as " + filename;
                }

                return $"Chunk {chunk.ChunkIndex + 1}/{chunk.TotalChunks} received. Waiting for others.";
            }
        }

        public string Multiply(string fileName1, string fileName2)
        {
            string dir = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "matrices");

            string path1 = Path.Combine(dir, fileName1);
            string path2 = Path.Combine(dir, fileName2);

            if (!File.Exists(path1) || !File.Exists(path2))
                throw new FileNotFoundException("One or both matrix files not found.");

            int[][] matrixA = ReadMatrixFromFile(path1);
            int[][] matrixB = ReadMatrixFromFile(path2);

            if (matrixA[0].Length != matrixB.Length)
                throw new InvalidOperationException("Matrix dimensions are incompatible for multiplication.");

            int[][] result = Multiply(matrixA, matrixB);

            return SaveMatrixToFile(result, dir);
        }

        private int[][] Multiply(int[][] matrixA, int[][] matrixB)
        {
            int rows = matrixA.Length;
            int cols = matrixB[0].Length;
            int common = matrixA[0].Length;

            int[][] result = new int[rows][];
            for (int i = 0; i < rows; i++)
            {
                result[i] = new int[cols];
            }

            Parallel.For(0, rows, i =>
            {
                for (int j = 0; j < cols; j++)
                {
                    int sum = 0;
                    for (int k = 0; k < common; k++)
                    {
                        sum += matrixA[i][k] * matrixB[k][j];
                    }
                    result[i][j] = sum;
                }
            });

            return result;
        }

        private string SaveMatrixToFile(int[][] matrix, string dir)
        {
            int rows = matrix.Length;
            int cols = matrix[0].Length;

            string content = rows + " " + cols + "\n";

            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    content += matrix[i][j];

                    if (j < cols - 1)
                    {
                        content += " ";
                    }
                }

                content += "\n";
            }

            string filename = "matrix_" + DateTime.Now.ToString("yyyyMMdd_HHmmss") + ".txt";
            string path = Path.Combine(dir, filename);
            File.WriteAllText(path, content);

            return filename;
        }

        private int[][] ReadMatrixFromFile(string path)
        {
            string[] lines = File.ReadAllLines(path);
            string[] firstLineParts = lines[0].Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            int rows = int.Parse(firstLineParts[0]);
            int cols = int.Parse(firstLineParts[1]);

            int[][] matrix = new int[rows][];

            for (int i = 0; i < rows; i++)
            {
                string[] parts = lines[i + 1].Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                matrix[i] = new int[cols];

                for (int j = 0; j < cols; j++)
                {
                    matrix[i][j] = int.Parse(parts[j]);
                }
            }

            return matrix;
        }

        public string GetFromFile(string fileName)
        {
            string dir = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "matrices");
            string path = Path.Combine(dir, fileName);

            if (!File.Exists(path))
                throw new FileNotFoundException($"Matrix file '{fileName}' not found.");

            return File.ReadAllText(path);
        }
    }

}