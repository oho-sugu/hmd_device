#ifndef OLEDLib_h
#define OLEDLib_h

// Class definition
class OLEDLib
{
    public:
      OLEDLib(int respin, int cspin, int dcpin);
      int init();
      int fillRect(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int color);
      int putPixel(unsigned int x0, unsigned int y0, unsigned int color);
      int line(int x0, int y0, int x1, int y1, unsigned int color);
      int circle(unsigned int x0, unsigned int y0, unsigned int radius, unsigned int color);
      int drawNumber(unsigned int x0, unsigned int y0, unsigned int number, unsigned int color, unsigned int background);

    private:
      bool initialized;
      int respin;
      int cspin;
      int dcpin;
      int adjust_lining_limit(int *p_start, int *p_end, int sx, int sy, int ex, int ey, int *p_cx, int *p_cy);
      static byte font[150];

};

#endif

