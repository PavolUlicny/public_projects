// This code is a program that creates BMP images with specified dimensions, colors, and shapes.

// Include necessary headers
#include <fstream>
#include <cstdint>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

// BMPImageCreator class to create BMP images
class BMPImageCreator {
private:

    // Constants for BMP file format
    static constexpr short file_header_size = 14;
    static constexpr short bitmap_info_header_size = 40;
    static constexpr short pixel_info_offset = file_header_size + bitmap_info_header_size;

    // BMP File Header (14 bytes)
    unsigned char file_header[14] = { 0 };

	//initialize file header values
    int32_t width;
    int32_t height;
    int32_t padding_size;
    int32_t row_size;
    int32_t pixel_data_size;
    int32_t file_size;

    // Initialize DIB header values
    static constexpr int32_t bits_per_pixel = 24;
    static constexpr int32_t color_planes = 1;
    static constexpr int32_t compression = 0;
    static constexpr int32_t resolution = 2835;
    static constexpr int32_t colors_used = 0;
    static constexpr int32_t important_colors = 0;

    // DIB Header (BITMAPINFOHEADER, 40 bytes)
    unsigned char bitmap_info_header[40] = { 0 };

	// 2D vector to hold pixel data (RGB)
    std::vector<std::vector<std::array<unsigned char, 3>>> pixels;

public:

	// Constructor to initialize BMPImageCreator with specified width and height
    BMPImageCreator(int32_t width1, int32_t height1) {

		// Check for valid width and height, set default values if invalid
        if (width1 <= 0 || height1 <= 0) {
            width = 10;
            height = 5;

        } else {

            width = width1;
            height = height1;
        }

		// Set values to variables for BMP file header and DIB header
        padding_size = (4 - (width * 3) % 4) % 4;
        row_size = width * 3 + padding_size;
        pixel_data_size = row_size * height;
        file_size = file_header_size + bitmap_info_header_size + pixel_data_size;

		// Set the file header values
        file_header[0] = 'B';
        file_header[1] = 'M';
        file_header[10] = static_cast<unsigned char>(pixel_info_offset);
        file_header[11] = static_cast<unsigned char>(pixel_info_offset >> 8);
        file_header[12] = static_cast<unsigned char>(pixel_info_offset >> 16);
        file_header[13] = static_cast<unsigned char>(pixel_info_offset >> 24);

		// Set file size in the file header
        file_header[2] = static_cast<unsigned char>(file_size);
        file_header[3] = static_cast<unsigned char>(file_size >> 8);
        file_header[4] = static_cast<unsigned char>(file_size >> 16);
        file_header[5] = static_cast<unsigned char>(file_size >> 24);

        // Set DIB header size
        bitmap_info_header[0] = static_cast<unsigned char>(bitmap_info_header_size);

        // Width
        bitmap_info_header[4] = static_cast<unsigned char>(width);
        bitmap_info_header[5] = static_cast<unsigned char>(width >> 8);
        bitmap_info_header[6] = static_cast<unsigned char>(width >> 16);
        bitmap_info_header[7] = static_cast<unsigned char>(width >> 24);

        // Height
        bitmap_info_header[8] = static_cast<unsigned char>(height);
        bitmap_info_header[9] = static_cast<unsigned char>(height >> 8);
        bitmap_info_header[10] = static_cast<unsigned char>(height >> 16);
        bitmap_info_header[11] = static_cast<unsigned char>(height >> 24);

        // Color planes
        bitmap_info_header[12] = static_cast<unsigned char>(color_planes);

        // Bits per pixel
        bitmap_info_header[14] = static_cast<unsigned char>(bits_per_pixel);

        // Compression
        bitmap_info_header[16] = static_cast<unsigned char>(compression);

        // Raw image size
        bitmap_info_header[20] = static_cast<unsigned char>(pixel_data_size);
        bitmap_info_header[21] = static_cast<unsigned char>(pixel_data_size >> 8);
        bitmap_info_header[22] = static_cast<unsigned char>(pixel_data_size >> 16);
        bitmap_info_header[23] = static_cast<unsigned char>(pixel_data_size >> 24);

        // Horizontal resolution
        bitmap_info_header[24] = static_cast<unsigned char>(resolution);
        bitmap_info_header[25] = static_cast<unsigned char>(resolution >> 8);
        bitmap_info_header[26] = static_cast<unsigned char>(resolution >> 16);
        bitmap_info_header[27] = static_cast<unsigned char>(resolution >> 24);

        // Vertical resolution
        bitmap_info_header[28] = static_cast<unsigned char>(resolution);
        bitmap_info_header[29] = static_cast<unsigned char>(resolution >> 8);
        bitmap_info_header[30] = static_cast<unsigned char>(resolution >> 16);
        bitmap_info_header[31] = static_cast<unsigned char>(resolution >> 24);

        // Colors used
        bitmap_info_header[32] = static_cast<unsigned char>(colors_used);

        // Important colors
        bitmap_info_header[36] = static_cast<unsigned char>(important_colors);

        // Create 2D pixel vector as RGB
        pixels = std::vector<std::vector<std::array<unsigned char, 3>>>(height, std::vector<std::array<unsigned char, 3>>(width, { 255, 255, 255 }));

	}

	// Function to set the default pixel RGB color for the entire image
    void setDefaultPixelRGB(int r, int g, int b) {

        r = std::clamp(r, 0, 255);
        g = std::clamp(g, 0, 255);
        b = std::clamp(b, 0, 255);
        
		// Set the default pixel RGB color for the entire image
        for (size_t y = 0; y < height; ++y) {
            for (size_t x = 0; x < width; ++x) {
                pixels[y][x] = { static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b) };
            }
        }
	}

	// Function to set a pixel at (x, y) with RGB values
    void setPixel(int32_t x, int32_t y, int r, int g, int b) {

		// Check if the pixel coordinates are within bounds
        if (x >= width || x < 0 || y >= height || y < 0) {
			return;
        }

        r = std::clamp(r, 0, 255);
        g = std::clamp(g, 0, 255);
        b = std::clamp(b, 0, 255);

		// Set the pixel at (x, y) with the specified RGB values
        pixels[y][x] = { static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b) };
	}

    void createRectangle(int32_t x, int32_t y, int32_t x1, int32_t y1, int r, int g, int b, bool fill) {

		// Swap coordinates to ensure x1 >= x and y1 >= y
        if (x1 < x) {
            std::swap(x, x1);
        }
        if (y1 < y) {
            std::swap(y, y1);
        }

		// If fill is true, fill the rectangle with the specified color
        if (fill) {
            for (int32_t i = y; i <= y1; ++i) {
                for (int32_t j = x; j <= x1; ++j) {
                    setPixel(j, i, r, g, b);
                }
            }
        }

		// If fill is false, draw only the border of the rectangle
        else {

            for (int32_t i = x; i <= x1; ++i) {
                setPixel(i, y, r, g, b);
                setPixel(i, y1, r, g, b);
            }
            for (int32_t j = y; j <= y1; ++j) {
                setPixel(x, j, r, g, b);
                setPixel(x1, j, r, g, b);
            }
        }
    }

	// Function to create a line using Bresenham's algorithm
    void createLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int r, int g, int b) {

		// Find the horizontal distance between the two points 
        int32_t horizontal_distance = abs(x1 - x0);

		// Find the vertical distance between the two points
        int32_t vertical_distance = -abs(y1 - y0);

		// If the line is a single point, set that pixel
        if (horizontal_distance == 0 && vertical_distance == 0) {
            setPixel(x0, y0, r, g, b);
            return;
		}

        short horizontal_direction;
        short vertical_direction;

		// Determine the direction of the line
        if (x0 < x1) {
			horizontal_direction = 1;
        } else {
			horizontal_direction = -1;
		}

		if (y0 < y1) {
            vertical_direction = 1;
		} else {
            vertical_direction = -1;
        }

        long error_value = horizontal_distance + vertical_distance;

		// Loop until the line is drawn
        while (true) {
            setPixel(x0, y0, r, g, b);

            if (x0 == x1 && y0 == y1) {
                break;
            }

            long double_error_value = 2 * error_value;

            if (double_error_value >= vertical_distance) {
                error_value += vertical_distance;
                x0 += horizontal_direction;
            }

            if (double_error_value <= horizontal_distance) {
                error_value += horizontal_distance;
                y0 += vertical_direction;
            }
        }
    }

	// Function to create a circle using the Midpoint Circle Algorithm
    void createCircle(int32_t centerX, int32_t centerY, int32_t radius, int r, int g, int b, bool fill) {

		// Check if the radius is valid
        if (radius <= 0) {
            return;
        }

        int32_t x = radius;
        int y = 0;
        int error = 0;

		// Start drawing the circle using the Midpoint Circle Algorithm
        while (x >= y) {

			// Draw symmetric points in all octants
            if (fill) {

                // Draw horizontal scanlines between symmetric points
                for (int i = centerX - x; i <= centerX + x; ++i) {
                    setPixel(i, centerY + y, r, g, b);
                    setPixel(i, centerY - y, r, g, b);
                }

                for (int i = centerX - y; i <= centerX + y; ++i) {
                    setPixel(i, centerY + x, r, g, b);
                    setPixel(i, centerY - x, r, g, b);
                }

            } else {

                // Only draw circle perimeter points
                setPixel(centerX + x, centerY + y, r, g, b);
                setPixel(centerX + y, centerY + x, r, g, b);
                setPixel(centerX - y, centerY + x, r, g, b);
                setPixel(centerX - x, centerY + y, r, g, b);
                setPixel(centerX - x, centerY - y, r, g, b);
                setPixel(centerX - y, centerY - x, r, g, b);
                setPixel(centerX + y, centerY - x, r, g, b);
                setPixel(centerX + x, centerY - y, r, g, b);
            }

			// Calculate the next point using the Midpoint Circle Algorithm
            y += 1;
            error += 2 * y + 1;

            if (2 * (error - x) + 1 > 0) {
                x -= 1;
                error += 1 - 2 * x;
            }
        }
    }

	// Function to save the BMP image to a file
    void saveFile(const std::string& filename) {

        // Flatten pixel data (convert RGB to BGR and reverse rows)
        std::vector<unsigned char> pixel_data(pixel_data_size, 0);
        for (size_t y = 0; y < height; ++y) {
            size_t row_start = y * row_size;
            const size_t src_y = height - 1 - y;
            for (size_t x = 0; x < width; ++x) {
                size_t i = row_start + x * 3;
                const auto& rgb = pixels[src_y][x];
                pixel_data[i + 0] = rgb[2];
                pixel_data[i + 1] = rgb[1];
                pixel_data[i + 2] = rgb[0];
            }
        }

	    std::string filename1 = filename + ".bmp";

        // Write to file
        std::ofstream file(filename1, std::ios::binary);
        if (!file) {
            return;
        }

        file.write(reinterpret_cast<char*>(file_header), sizeof(file_header));
        file.write(reinterpret_cast<char*>(bitmap_info_header), sizeof(bitmap_info_header));
        file.write(reinterpret_cast<char*>(pixel_data.data()), pixel_data_size);

        file.close();

    }
};

int main() {

	// Example usage of BMPImageCreator
	// BMPImageCreator bmp(100, 100);
	// bmp.setDefaultPixelRGB(255, 0, 0);  Set default pixel color to red
	// bmp.createRectangle(10, 10, 90, 90, 0, 255, 0, true);  Create a filled green rectangle
	// bmp.createLine(10, 10, 90, 90, 0, 0, 255);  Create a blue line
	// bmp.createCircle(50, 50, 30, 255, 255, 0, false);  Create a yellow circle outline
	// bmp.saveFile("output_image");  Save the BMP image to a file

    return 0;
}
