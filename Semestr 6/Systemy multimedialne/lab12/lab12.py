import numpy as np
import matplotlib.pyplot as plt
import cv2
from skimage.metrics import mean_squared_error as mse
from skimage.metrics import structural_similarity as ssim

IMAGE_WIDTH = 640
IMAGE_HEIGHT = 480

def draw_line(buffer, p1, p2, color):
    x0, y0 = p1
    x1, y1 = p2
    dx = abs(x1 - x0)
    dy = abs(y1 - y0)
    sx = 1 if x0 < x1 else -1
    sy = 1 if y0 < y1 else -1
    err = dx - dy

    while True:
        if 0 <= x0 < buffer.shape[1] and 0 <= y0 < buffer.shape[0]:
            buffer[y0, x0] = color
        if x0 == x1 and y0 == y1:
            break
        e2 = 2 * err
        if e2 > -dy:
            err -= dy
            x0 += sx
        if e2 < dx:
            err += dx
            y0 += sy


def draw_circle(buffer, center, radius, color):
    x0, y0 = center
    x = radius
    y = 0
    err = 0

    while x >= y:
        points = [
            (x0 + x, y0 + y),
            (x0 + y, y0 + x),
            (x0 - y, y0 + x),
            (x0 - x, y0 + y),
            (x0 - x, y0 - y),
            (x0 - y, y0 - x),
            (x0 + y, y0 - x),
            (x0 + x, y0 - y),
        ]
        for px, py in points:
            if 0 <= px < buffer.shape[1] and 0 <= py < buffer.shape[0]:
                buffer[py, px] = color
        y += 1
        if err <= 0:
            err += 2 * y + 1
        if err > 0:
            x -= 1
            err -= 2 * x + 1

    circle_points = []
    for angle in range(0, 360, 5):
        rad = np.deg2rad(angle)
        px = int(x0 + radius * np.cos(rad))
        py = int(y0 + radius * np.sin(rad))
        circle_points.append((px, py))

    return circle_points


def draw_polygon(buffer, points, color):
    n = len(points)
    for i in range(n):
        p_start = points[i]
        p_end = points[(i + 1) % n]
        draw_line(buffer, p_start, p_end, color)
    return points


def draw_triangle(buffer, p1, p2, p3, color):
    draw_line(buffer, p1, p2, color)
    draw_line(buffer, p2, p3, color)
    draw_line(buffer, p3, p1, color)
    return [p1, p2, p3]


def draw_rectangle(buffer, p1, p2, color):
    x1, y1 = p1
    x2, y2 = p2
    corners = [(x1, y1), (x2, y1), (x2, y2), (x1, y2)]
    for i in range(4):
        draw_line(buffer, corners[i], corners[(i + 1) % 4], color)
    return corners


def draw(image_data, target_size=None):
    original_width = image_data["Canvas"]["width"]
    original_height = image_data["Canvas"]["height"]

    if target_size:
        scale_x = target_size[0] / original_width
        scale_y = target_size[1] / original_height
    else:
        scale_x = scale_y = 1.0

    width = int(original_width * scale_x)
    height = int(original_height * scale_y)

    bg_color = image_data["Canvas"]["background_color"]
    buffer = np.zeros((height, width, 4), dtype=np.uint8)
    buffer[..., :3] = bg_color
    buffer[..., 3] = 255

    shapes = sorted(image_data["Shapes"], key=lambda s: s.get("Z_layer", 0))

    for shape in shapes:
        color_rgb = shape["color"]
        color = np.array([*color_rgb, 255], dtype=np.uint8)

        if shape["type"] == "circle":
            center = (int(shape["center"][1] * scale_y), int(shape["center"][0] * scale_x))
            radius = int(shape["radius"] * scale_x)
            polygon_points = draw_circle(buffer, center, radius, color)
            fill_polygon(buffer, polygon_points, color)

        elif shape["type"] == "line":
            p1 = (int(shape["p1"][1] * scale_y), int(shape["p1"][0] * scale_x))
            p2 = (int(shape["p2"][1] * scale_y), int(shape["p2"][0] * scale_x))
            draw_line(buffer, p1, p2, color)

        elif shape["type"] == "rectangle":
            p1 = (int(shape["p1"][1] * scale_y), int(shape["p1"][0] * scale_x))
            p2 = (int(shape["p2"][1] * scale_y), int(shape["p2"][0] * scale_x))
            polygon_points = draw_rectangle(buffer, p1, p2, color)
            fill_polygon(buffer, polygon_points, color)

        elif shape["type"] == "triangle":
            p1 = (int(shape["p1"][1] * scale_y), int(shape["p1"][0] * scale_x))
            p2 = (int(shape["p2"][1] * scale_y), int(shape["p2"][0] * scale_x))
            p3 = (int(shape["p3"][1] * scale_y), int(shape["p3"][0] * scale_x))
            polygon_points = draw_triangle(buffer, p1, p2, p3, color)
            fill_polygon(buffer, polygon_points, color)

        elif shape["type"] == "freeform":
            points = [(int(p[1] * scale_y), int(p[0] * scale_x)) for p in shape["points"]]
            polygon_points = draw_polygon(buffer, points, color)
            fill_polygon(buffer, polygon_points, color)

    return buffer


def fill_polygon(buffer, points, color):
    points = [(int(x), int(y)) for (x, y) in points]

    ys = [p[1] for p in points]
    min_y = max(min(ys), 0)
    max_y = min(max(ys), buffer.shape[0] - 1)

    for y in range(min_y, max_y + 1):
        intersections = []
        for i in range(len(points)):
            p1 = points[i]
            p2 = points[(i + 1) % len(points)]

            if p1[1] == p2[1]:
                continue

            if (p1[1] <= y < p2[1]) or (p2[1] <= y < p1[1]):
                x = p1[0] + (y - p1[1]) * (p2[0] - p1[0]) / (p2[1] - p1[1])
                intersections.append(int(x))

        intersections.sort()

        for i in range(0, len(intersections), 2):
            if i + 1 < len(intersections):
                x_start = max(intersections[i], 0)
                x_end = min(intersections[i + 1], buffer.shape[1] - 1)
                for x in range(x_start, x_end + 1):
                    buffer[y, x] = color


Example = {
    "Canvas": {
        "width": 640,
        "height": 480,
        "background_color": [255, 255, 255] # white
    },
    "Shapes": [
        {
            "type": "circle",
            "Z_layer": 0,
            "center": [100, 150],
            "radius": 80,
            "color": [0, 0, 255] # blue
        },
        {
            "type": "triangle",
            "Z_layer": 1,
            "p1": [100, 100],
            "p2": [200, 190],
            "p3": [130, 250],
            "color": [255, 0, 0] # red
        },
        {
            "type": "rectangle",
            "Z_layer": 0,
            "p1": [350, 100],
            "p2": [500, 250],
            "color": [0, 255, 0] # green
        },
        {
            "type": "rectangle",
            "Z_layer": 1,
            "p1": [370, 120],
            "p2": [410, 160],
            "color": [255, 255, 0] # yellow
        },
        {
            "type": "rectangle",
            "Z_layer": 1,
            "p1": [440, 120],
            "p2": [480, 160],
            "color": [255, 255, 0] # yellow
        },
        {
            "type": "freeform",
            "Z_layer": 2,
            "points": [
                [50, 450],
                [300, 450],
                [300, 600],
                [250, 600],
                [250, 500],
                [50, 500]
            ],
            "color": [0, 128, 128] # cyan
        },
        {
            "type": "rectangle",
            "Z_layer": 1,
            "p1": [380, 350],
            "p2": [550, 450],
            "color": [139, 69, 19] # brown
        },
        {
            "type": "circle",
            "Z_layer": 0,
            "center": [430, 450],
            "radius": 40,
            "color": [255, 255, 0] # yellow
        },
        {
            "type": "freeform",
            "Z_layer": 1,
            "points": [
                [280, 280],
                [330, 330],
                [280, 380],
                [230, 330]
            ],
            "color": [255, 0, 0]  # red
        },
        {
            "type": "rectangle",
            "Z_layer": 0,
            "p1": [230, 280],
            "p2": [330, 380],
            "color": [0, 255, 0]  # green
        },
        {
            "type": "circle",
            "Z_layer": 0,
            "center": [280, 220],
            "radius": 50,
            "color": [0, 0, 0]  # black
        }
    ]
}

sizes = [
    (320, 240),
    (480, 360),
    (800, 600),
    (1024, 768),
]

img_ref = draw(image_data=Example, target_size=(640, 480))

plt.imshow(img_ref)
plt.axis('off')
plt.show()

images = []

for sz in sizes:
    img = draw(Example, target_size=sz)
    images.append((sz, img))

resized = []

for sz, img in images:
    resized_img = cv2.resize(img, (640, 480), interpolation=cv2.INTER_AREA)
    resized.append((sz, resized_img))

for sz, img in resized:
    m = mse(img_ref, img)
    s = ssim(img_ref, img, channel_axis=-1)

    plt.imshow(img)
    plt.axis('off')
    plt.show()

    print(f"Size {sz}: MSE = {m}, SSIM = {s}")
