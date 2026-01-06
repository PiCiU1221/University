using System.Runtime.Serialization;
using System.ServiceModel;

namespace WcfService1
{
    [ServiceContract]
    public interface IService1
    {
        [OperationContract]
        string UploadMatrixChunk(MatrixChunk chunk);

        [OperationContract]
        string MultiplyMatrices(string fileName1, string fileName2);

        [OperationContract]
        string GetMatrixFromFile(string fileName);

        [OperationContract]
        string GenerateMandelbrot(int width, int height, int threadCount);

        [OperationContract]
        byte[] GetMandelbrotFragment(string filename, int x1, int y1, int x2, int y2);
    }

    [DataContract]
    public class MatrixChunk
    {
        [DataMember]
        public string MatrixId { get; set; }

        [DataMember]
        public int ChunkIndex { get; set; }

        [DataMember]
        public int TotalChunks { get; set; }

        [DataMember]
        public string ChunkData { get; set; }
    }
}