#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight) {
    m_pixel_size = { pixelWidth, pixelHeight };
    m_aspectRatio = (pixelHeight*1.0)/(pixelWidth*1.0);
    m_plane_center = { 0,0 };
    m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
    m_zoomCount = 0;
    m_State = State::CALCULATING;
    m_vArray.setPrimitiveType(Points);
    m_vArray.resize(pixelWidth * pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const {
    target.draw(m_vArray);
}

void ComplexPlane::updateRender() {
    if(m_State == State::CALCULATING)
    {
        size_t iterations = 0;
        for(int i = 0; i < m_pixel_size.y; i++)
        {
            for(int j = 0; j < m_pixel_size.x; j++)
            {
                m_vArray[j + i * m_pixel_size.x].position = {(float)j, (float)i};
                Vector2f coord = mapPixelToCoords(Vector2i(j, i));
                iterations = countIterations(coord);
                Uint8 r, g, b;
                iterationsToRGB(iterations, r, g, b);
                m_vArray[j + i * m_pixel_size.x].color = {r, g, b};
            }
        }
    }
    m_State = State::DISPLAYING;
}

void ComplexPlane::zoomIn() {
    m_zoomCount++;
	float xSize = BASE_WIDTH * (pow(BASE_ZOOM,m_zoomCount));
	float ySize = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM,m_zoomCount));
	m_plane_size = {xSize,ySize};
	m_State = State::CALCULATING;
}

void ComplexPlane::zoomOut() {
    m_zoomCount--;
	float xSize = BASE_WIDTH * (pow(BASE_ZOOM,m_zoomCount));
	float ySize = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM,m_zoomCount));
	m_plane_size = {xSize,ySize};
	m_State = State::CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel) {
    m_plane_center = mapPixelToCoords(mousePixel);
    m_State = State::CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel) {
    m_mouseLocation = mapPixelToCoords(mousePixel);
}

void ComplexPlane::loadText(Text& text) {
    ostringstream strm;
    strm << "Mandelbrot Set \n" << 
            "Center: (" << m_plane_center.x << "," << m_plane_center.y << ") \n" <<
            "Cursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ") \n" <<
            "Left-click to Zoom in \n" << 
            "Right-click to Zoom out \n";
    
    text.setString(strm.str());
}

size_t ComplexPlane::countIterations(Vector2f coord) {
    size_t count = 0;
    Vector2f z = coord;

    while(count < MAX_ITER) {
        float x = z.x * z.x - z.y * z.y + coord.x;
        float y = 2.0 * z.x * z.y + coord.y;

        z = Vector2f(x,y);

        if(z.x * z.x + z.y * z.y > 4.0) { break; }
        count++;
    }
    
    return count;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b) {
    if (count == MAX_ITER) {
        r = 0;
        g = 0;
        b = 0;
    }
    else if (count == 0 && count < 8) {
        r = 204;
        g = 0;
        b = 0;
    }
    else if (count >= 8 && count < 16) {
        r = 204;
        g = 102;
        b = 0;
    }
    else if (count >= 16 && count < 24) {
        r = 255;
        g = 255;
        b = 102;
    }
    else if (count >= 24 && count < 32) {
        r = 102;
        g = 178;
        b = 255;
    }
    else if (count >= 32 && count < 40) {
        r = 178;
        g = 102;
        b = 255;
    }
    else if (count >= 40 && count < 48){
        r = 255;
        b = 153;
        g = 255;
    }
    else if (count >= 48 && count < 56) {
        r = 255;
        b = 204;
        g = 229;
    }
    else {
        r = 255;
        g = 255;
        b = 255;
    }
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel) {
    Vector2f planeCord;
    planeCord.x = ((mousePixel.x - 0) / (1.0 * m_plane_size.x - 0) ) * (m_plane_size.x) + (m_plane_center.x - m_plane_size.x / 2.0);
    planeCord.y = ((mousePixel.y - m_plane_size.y) / (0 - m_plane_size.y * 1.0)) * (m_plane_size.y) + (m_plane_center.y - m_plane_size.y / 2.0);
    return planeCord;
} 