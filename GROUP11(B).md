Suppose you have a system with a 12 inch by 14 inch video monitor that can display 120 pixels per inch. If memory is organized in one byte words, the starting frame buffer address is 0 , and each pixel is assigned 4 bits of storage, what is the frame buffer address of the pixel with screen coordinates (x,y)?

Explanation
To compute the frame buffer address for pixel (x,y):

1. Convert physical size (in inches) to resolution (in pixels).
2. Calculate the pixel's offset in the frame buffer.
3. Account for pixels per row (screen width in pixels).
4. Each pixel is 4 bits (0.5 bytes), so half a byte per pixel.
5. Calculate the byte address from pixel number (since each memory location is 1 byte, and 2 pixels fit in a byte), starting at address 0.

Step-By-Step Solution
Step 1
Compute resolution (pixels per dimension):
• Width in pixels: 12 inches × 120 pixels/inch =1440 pixels
• Height in pixels: 14 inches × 120 pixels/inch =1680 pixels

Step 2
Calculate pixel offset for (x,y):
• Screen coordinates: (x,y) where x is column (0 to 1439), y is row (0 to 1679).
• Offset (in pixels): offset=y×1440+x

Step 3
Calculate the byte address for this pixel:
• Each pixel needs 4 bits =0.5 bytes.
• So, 2 pixels are stored per byte.
Therefore, pixel n is stored at byte address: byte address=⌊2offset⌋

Step 4
Substitute the offset: byte address=⌊2y×1440+x⌋
Final Answer
The frame buffer address of the pixel at screen coordinates (x,y) is:
⌊(y×1440+x)/2⌋
where x=0 to 1439 and y=0 to 1679.
