namespace WebApplication1.Models
{
    public class MatrixChunk
    {
        public string MatrixId { get; set; }
        public int ChunkIndex { get; set; }
        public int TotalChunks { get; set; }
        public string ChunkData { get; set; }
    }
}
