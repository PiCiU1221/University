using Microsoft.AspNetCore.Mvc;
using WcfService1.services;

namespace WebApplication1.Controllers
{
    [ApiController]
    [Route("api/mandelbrot")]
    public class MandelbrotController : ControllerBase
    {
        private readonly MandelbrotService _service = new MandelbrotService();

        [HttpPost("generate")]
        public IActionResult Generate([FromQuery] int width, [FromQuery] int height, [FromQuery] int threads)
        {
            var fileName = _service.GenerateMandelbrot(width, height, threads);
            return Ok(fileName);
        }

        [HttpGet("fragment")]
        public IActionResult GetFragment([FromQuery] string filename, [FromQuery] int x1, [FromQuery] int y1, [FromQuery] int x2, [FromQuery] int y2)
        {
            var data = _service.GetMandelbrotFragment(filename, x1, y1, x2, y2);
            return File(data, "image/png");
        }
    }
}
