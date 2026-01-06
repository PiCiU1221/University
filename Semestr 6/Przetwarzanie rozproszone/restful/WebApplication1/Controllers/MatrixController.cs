using Microsoft.AspNetCore.Mvc;
using WcfService1;
using WebApplication1.Models;

namespace WebApplication1.Controllers
{
    [ApiController]
    [Route("api/matrix")]
    public class MatrixController : ControllerBase
    {
        private readonly MatrixService _matrixService = new MatrixService();

        [HttpPost("upload")]
        public IActionResult UploadMatrixChunk([FromBody] MatrixChunk chunk)
        {
            var result = _matrixService.UploadChunk(chunk);
            return Ok(result);
        }

        [HttpPost("multiply")]
        public IActionResult Multiply([FromQuery] string fileName1, [FromQuery] string fileName2)
        {
            var result = _matrixService.Multiply(fileName1, fileName2);
            return Ok(result);
        }

        [HttpGet("{fileName}")]
        public IActionResult GetMatrix(string fileName)
        {
            var result = _matrixService.GetFromFile(fileName);
            return Ok(result);
        }
    }
}
