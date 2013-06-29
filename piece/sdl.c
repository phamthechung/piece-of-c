void ComplainAndExit(void)
{
    fprintf(stderr, "Problem: %s\n", SDL_GetError());
    exit(1);
}

int main(int argc, char *argv[])
{
    SDL_PixelFormat fmt;
    SDL_Surface *screen, *locked;
    SDL_Surface *imagebmp, *image;
    SDL_Rect dstrect;
    int i;
    Uint8 *buffer;

    /* Initialize SDL */
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        ComplainAndExit();
    }
    atexit(SDL_Quit);

    /* Load a BMP image into a surface */
    imagebmp = SDL_LoadBMP("image.bmp");
    if ( imagebmp == NULL ) {
        ComplainAndExit();
    }

    /* Set the video mode (640x480 at native depth) */
    screen = SDL_SetVideoMode(640, 480, 0, SDL_HWSURFACE|SDL_FULLSCREEN);
    if ( screen == NULL ) {
        ComplainAndExit();
    }

    /* Set the video colormap */
    if ( imagebmp->format->palette != NULL ) {
        SDL_SetColors(screen,
                      imagebmp->format->palette->colors, 0,
                      imagebmp->format->palette->ncolors);
    }

    /* Convert the image to the video format (maps colors) */
    image = SDL_DisplayFormat(imagebmp);
    SDL_FreeSurface(imagebmp);
    if ( image == NULL ) {
        ComplainAndExit();
    }

    /* Draw bands of color on the raw surface */
    if ( SDL_MUSTLOCK(screen) ) {
        if ( SDL_LockSurface(screen) < 0 )
            ComplainAndExit();
    }
    buffer=(Uint8 *)screen->pixels;
    for ( i=0; i<screen->h; ++i ) {
        memset(buffer,(i*255)/screen->h,
               screen->w*screen->format->BytesPerPixel);
               buffer += screen->pitch;
    }
    if ( SDL_MUSTLOCK(screen) ) {
        SDL_UnlockSurface(screen);
    }

    /* Blit the image to the center of the screen */
    dstrect.x = (screen->w-image->w)/2;
    dstrect.y = (screen->h-image->h)/2;
    dstrect.w = image->w;
    dstrect.h = image->h;
    if ( SDL_BlitSurface(image, NULL, screen, &dstrect) < 0 ) {
        SDL_FreeSurface(image);
        ComplainAndExit();
    }
    SDL_FreeSurface(image);

    /* Update the screen */
    SDL_UpdateRects(screen, 1, &dstrect);

    SDL_Delay(5000);        /* Wait 5 seconds */
    exit(0);
}

