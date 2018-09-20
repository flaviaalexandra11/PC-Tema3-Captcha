//Popescu Flavia-Alexandra 311CD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp_header.h"
#define N 101

typedef struct
{
	int B, G, R;

}pixel;

typedef struct
{
    int y, x, digit, B, G, R;

}number;

int B, G, R, toDel[10], v[30] = {0}, d = 0, n = 0;
unsigned char image[30], templ[10][5][5], mat[N][N],
task1[30], task2[30], task3[30];


bmp_fileheader fileHeader;
bmp_infoheader infoHeader;
pixel a[N][N];
number poz[N], rpoz[N];

//citire din fisierul input.txt

void readInput(FILE *input)
{
	int i;
	unsigned char str[60];

	fgets(image, 40, input);
	image[strlen(image) -1] = '\0';

	fscanf(input, "%d%d%d", &B, &G, &R);

	fgetc(input);
	fgets(str, 60, input);

	for(i = 0; i < strlen(str); i++)
		if((str[i] != ' ') && (str[i] != '\n'))
		{
			toDel[d] = str[i] - 48;
			d++;
		}
}

//citirea fisierului bmp

void readCaptcha(FILE *captcha)
{
	unsigned int x, i, j;
	unsigned char c;
	unsigned short s;

	//citire header
	fileHeader.fileMarker1 = fgetc(captcha);
	fileHeader.fileMarker2 = fgetc(captcha);

	fread(&x, sizeof(unsigned int), 1, captcha);
	fileHeader.bfSize = x;

	fread(&s, sizeof(unsigned short), 1, captcha);
	fileHeader.unused1 = s;

	fread(&s, sizeof(unsigned short), 1, captcha);
	fileHeader.unused2 = s;

	fread(&x, sizeof(unsigned int), 1, captcha);
	fileHeader.imageDataOffset = x;


	fread(&x, sizeof(int), 1, captcha);
	infoHeader.biSize = x;

	fread(&x, sizeof(int), 1, captcha);
	infoHeader.width = x;

	fread(&x, sizeof(int), 1, captcha);
	infoHeader.height = x;

	fread(&s, sizeof(short), 1, captcha);
	infoHeader.planes = s;

	fread(&s, sizeof(short), 1, captcha);
	infoHeader.bitPix = s;

	fread(&x, sizeof(int), 1, captcha);
	infoHeader.biCompression = x;

	fread(&x, sizeof(int), 1, captcha);
	infoHeader.biSizeImage = x;

	fread(&x, sizeof(int), 1, captcha);
	infoHeader.biXPelsPerMeter = x;

	fread(&x, sizeof(int), 1, captcha);
	infoHeader.biYPelsPerMeter = x;

	fread(&x, sizeof(int), 1, captcha);
	infoHeader.biClrUsed = x;

	fread(&x, sizeof(int), 1, captcha);
	infoHeader.biClrImportant = x;

	//calcul padding
	int pad = (infoHeader.width*3)%4;
	if(pad) pad=4-pad;

	//citire bitmap
	for(i = infoHeader.height; i >= 1; i--)
	{
		for(j = 1; j <= infoHeader.width; j++)
		{
			c = 0;
			fread(&c, sizeof(unsigned char), 1, captcha);
			a[i][j].B = c;

			c = 0;
			fread(&c, sizeof(unsigned char), 1, captcha);
			a[i][j].G = c;

			c = 0;
			fread(&c, sizeof(unsigned char), 1, captcha);
			a[i][j].R = c;
		}

		for(j = 0; j < pad; j++)
		fgetc(captcha);
	}
}

//stabilirea numelor fisierelor rezultate

void name()
{
	int i, j;
	unsigned char nm[30] = {0}, cont1[11] = "_task1.bmp",
	cont2[11] = "_task2.txt", cont3[11] = "_task3.bmp";

	for(i = 0; image[i] != '.'; i++)
    {
        task1[i] = image[i];
        task2[i] = image[i];
        task3[i] = image[i];
    }

	for(j = 0; j < 10; j++)
    {
        task1[i+j] = cont1[j];
        task2[i+j] = cont2[j];
        task3[i+j] = cont3[j];
    }
}

//schimbarea culorii cifrelor

void newColor(char *captcha, FILE *newCaptcha)
{
    unsigned int x, i, j;
	int ni;
	unsigned short s;
	signed int si;
	unsigned char c;

	//calcul padding

    int pad = (infoHeader.width*3)%4;
    if (pad) pad=4-pad;

    //scriere in header

	c = fileHeader.fileMarker1;
	fwrite(&c, sizeof(unsigned char), 1, newCaptcha);

	c = fileHeader.fileMarker2;
	fwrite(&c, sizeof(unsigned char), 1, newCaptcha);

	x = fileHeader.bfSize;
	fwrite(&x, sizeof(unsigned int), 1, newCaptcha);

	s = fileHeader.unused1;
	fwrite(&s, sizeof(unsigned short), 1, newCaptcha);

	s = fileHeader.unused2;
	fwrite(&s, sizeof(unsigned short), 1, newCaptcha);

	x = fileHeader.imageDataOffset;
	fwrite(&x, sizeof(unsigned int), 1, newCaptcha);


	x = infoHeader.biSize;
	fwrite(&x, sizeof(signed int), 1, newCaptcha);

	si = infoHeader.width;
	fwrite(&si, sizeof(signed int), 1, newCaptcha);

	si = infoHeader.height;
	fwrite(&si, sizeof(signed int), 1, newCaptcha);

	s = infoHeader.planes;
	fwrite(&s, sizeof(unsigned short), 1, newCaptcha);

	s = infoHeader.bitPix;
	fwrite(&s, sizeof(unsigned short), 1, newCaptcha);

	x = infoHeader.biCompression;
	fwrite(&x, sizeof(unsigned int), 1, newCaptcha);

	x = infoHeader.biSizeImage;
	fwrite(&x, sizeof(unsigned int), 1, newCaptcha);

	ni = infoHeader.biXPelsPerMeter;
	fwrite(&ni, sizeof(int), 1, newCaptcha);

	ni = infoHeader.biYPelsPerMeter;
	fwrite(&ni, sizeof(int), 1, newCaptcha);

	x = infoHeader.biClrUsed;
	fwrite(&x, sizeof(unsigned int), 1, newCaptcha);

	x = infoHeader.biClrImportant;
	fwrite(&x, sizeof(unsigned int), 1, newCaptcha);

    //scriere bitmap cu noile culori

	for(i = infoHeader.height; i >= 1; i--)
	{
		for(j = 1; j <= infoHeader.width; j++)
		{
			if(a[i][j].B != 255 && a[i][j].G != 255 && a[i][j].R != 255)
			{
				c = B;
				fwrite(&c, sizeof(unsigned char), 1, newCaptcha);
				c = G;
				fwrite(&c, sizeof(unsigned char), 1, newCaptcha);
				c = R;
				fwrite(&c, sizeof(unsigned char), 1, newCaptcha);
			}

			else
			{
				c = a[i][j].B;
				fwrite(&c, sizeof(unsigned char), 1, newCaptcha);

				c = a[i][j].G;
				fwrite(&c, sizeof(unsigned char), 1, newCaptcha);

				c = a[i][j].R;
				fwrite(&c, sizeof(unsigned char), 1, newCaptcha);
			}
		}

		for(j = 0; j < pad; j++)
		{
			c = 0;
			fwrite(&c, sizeof(unsigned char), 1, newCaptcha);
		}
	}
}

void templates()
{
    int i, j, k = 0;
    unsigned char rawTempl[10][26];

    //creez matrice cu template-uri pentru cifre

    strcpy(rawTempl[0], "XXXXXX...XX...XX...XXXXXX");
    strcpy(rawTempl[1], "....X....X....X....X....X");
    strcpy(rawTempl[2], "XXXXX....XXXXXXX....XXXXX");
    strcpy(rawTempl[3], "XXXXX....XXXXXX....XXXXXX");
    strcpy(rawTempl[4], "X...XX...XXXXXX....X....X");
    strcpy(rawTempl[5], "XXXXXX....XXXXX....XXXXXX");
    strcpy(rawTempl[6], "XXXXXX....XXXXXX...XXXXXX");
    strcpy(rawTempl[7], "XXXXX....X....X....X....X");
    strcpy(rawTempl[8], "XXXXXX...XXXXXXX...XXXXXX");
    strcpy(rawTempl[9], "XXXXXX...XXXXXX....XXXXXX");

    //transpun template-urile intr-un vector de matrice

    for(i = 0; i < 10; i++)
        {
            k = 0;
            for(j = 0; j < 25; j++)
                {
                    if((j+1)%5 == 0)
                    {
                        k = 0;
                        templ[i][k][j] = rawTempl[i][j];
                    }
                    else
                        templ[i][k][j] = rawTempl[i][j];
                }
            k++;
        }
}

    //creez o matrice echivalenta bitmap-ului cu 'X' si '.'

void pixelMatrix()
{
    int i, j;

    for(i = 1; i <= infoHeader.height; i++)
        for(j = 1; j <= infoHeader.width; j++)
            if((a[i][j].B != 255)||(a[i][j].G != 255)||(a[i][j].R != 255))
                {
                    mat[i][j] = 'X';
                }
            else
                mat[i][j] = '.';
}

// caut in matricea echivalenta bitmapului elemnte din template

int checkDigit(int m, int n)
{
    int i, j, k, ok = 0;
    unsigned char proba[5][5];

    for(i = 0; i < 5; i++)
        for(j = 0; j < 5; j++)
            proba[i][j] = mat[m-4+i][n-4+j];

    for(k = 0; k <= 9; k++)
    {
        ok = 0;
        for(i = 0; i < 5; i++)
            for(j = 0; j < 5; j++)
                if(proba[i][j] != templ[k][i][j])
                ok = 1;

        if(ok == 0 && mat[m+1][n] != 'X' && mat[m][n+1] != 'X')
            return k;
    }
    return -1;
}

//retin cifrele gasite

void writeDigits(FILE *numbers)
{
    int i, j, k, ok = 0;

    for(j = infoHeader.width; j>=1; j--)
        for(i = infoHeader.height; i >= 1; i--)
            if(mat[i][j] == 'X')
            {
                if(checkDigit(i,j) != -1)
                {
                    v[n] = checkDigit(i,j);

                    poz[n].y = i;
                    poz[n].x = j;
                    poz[n].digit = v[n];
                    poz[n].B = a[i][j].B;
                    poz[n].G = a[i][j].G;
                    poz[n].R = a[i][j].R;

                    n++;
                }
            }

    for(i = n-1; i >= 0; i--)
        {
            fprintf(numbers, "%d", v[i]);
        }
}

//sterg cifrele cerute

void delDigit(FILE *fewer)
{
	unsigned int x, i, j, k, r[30];
	int ni;
	unsigned short s;
	signed int si;
	unsigned char c;

	//header-ul - la fel ca la newCaptcha

	c = fileHeader.fileMarker1;
	fwrite(&c, sizeof(unsigned char), 1, fewer);

	c = fileHeader.fileMarker2;
	fwrite(&c, sizeof(unsigned char), 1, fewer);

	x = fileHeader.bfSize;
	fwrite(&x, sizeof(unsigned int), 1, fewer);

	s = fileHeader.unused1;
	fwrite(&s, sizeof(unsigned short), 1, fewer);

	s = fileHeader.unused2;
	fwrite(&s, sizeof(unsigned short), 1, fewer);

	x = fileHeader.imageDataOffset;
	fwrite(&x, sizeof(unsigned int), 1, fewer);

	x = infoHeader.biSize;
	fwrite(&x, sizeof(signed int), 1, fewer);

	si = infoHeader.width;
	fwrite(&si, sizeof(signed int), 1, fewer);

	si = infoHeader.height;
	fwrite(&si, sizeof(signed int), 1, fewer);

	s = infoHeader.planes;
	fwrite(&s, sizeof(unsigned short), 1, fewer);

	s = infoHeader.bitPix;
	fwrite(&s, sizeof(unsigned short), 1, fewer);

	x = infoHeader.biCompression;
	fwrite(&x, sizeof(unsigned int), 1, fewer);

	x = infoHeader.biSizeImage;
	fwrite(&x, sizeof(unsigned int), 1, fewer);

	ni = infoHeader.biXPelsPerMeter;
	fwrite(&ni, sizeof(int), 1, fewer);

	ni = infoHeader.biYPelsPerMeter;
	fwrite(&ni, sizeof(int), 1, fewer);

	x = infoHeader.biClrUsed;
	fwrite(&x, sizeof(unsigned int), 1, fewer);

	x = infoHeader.biClrImportant;
	fwrite(&x, sizeof(unsigned int), 1, fewer);

    //reordonez valorile

    for(i = 0; i < n; i++)
        {
            r[i] = v[n-1-i];

            rpoz[i].y = poz[n-1-i].y;
            rpoz[i].x = poz[n-1-i].x;
            rpoz[i].digit = poz[n-1-i].digit;
            rpoz[i].B = poz[n-1-i].B;
            rpoz[i].G = poz[n-1-i].G;
            rpoz[i].R = poz[n-1-i].R;
        }

    //sterg valorile nedorite

	for(j = 0; j < d; j++)
    {
        for(i = 0; i < n; i++)
        {
            if(r[i] == toDel[j])
                {
                    for(k = i; k < n ; k++)
                        {
                            r[k] = r[k+1];

                            rpoz[k].digit = rpoz[k+1].digit;
                            rpoz[k].B = rpoz[k+1].B;
                            rpoz[k].G = rpoz[k+1].G;
                            rpoz[k].R = rpoz[k+1].R;
                        }
                    n--;
                    i--;
                }
        }
    }

    //reinitializez matricele

    for(i = 1; i <= infoHeader.height; i++)
        for(j = 1; j <= infoHeader.width; j++)
        {
            mat[i][j] = '.';
            a[i][j].B = 255;
            a[i][j].G = 255;
            a[i][j].R = 255;
        }

    //modific culorile din matirce acolo unde este cazul

    for(k = 0; k < n; k++)
        for(i = 0; i < 5; i++)
            for(j = 0; j< 5; j++)
            {
                mat[rpoz[k].y-4+i][rpoz[k].x-4+j] = templ[rpoz[k].digit][i][j];

                if(mat[rpoz[k].y-4+i][rpoz[k].x-4+j] == 'X')
                {
                    a[rpoz[k].y-4+i][rpoz[k].x-4+j].B = rpoz[k].B;
                    a[rpoz[k].y-4+i][rpoz[k].x-4+j].G = rpoz[k].G;
                    a[rpoz[k].y-4+i][rpoz[k].x-4+j].R = rpoz[k].R;
                }

            }

    //completare bitmap

    int pad = (infoHeader.width*3)%4;
	if(pad) pad=4-pad;

	for(i = infoHeader.height; i >= 1; i--)
	{
		for(j = 1; j <= infoHeader.width; j++)
		{
            c = a[i][j].B;
            fwrite(&c, sizeof(unsigned char), 1, fewer);
            c = a[i][j].G;
            fwrite(&c, sizeof(unsigned char), 1, fewer);
            c = a[i][j].R;
            fwrite(&c, sizeof(unsigned char), 1, fewer);

		}

		for(j = 0; j < pad; j++)
		{
			c = 0;
			fwrite(&c, sizeof(unsigned char), 1, fewer);
		}
	}
}

int main()
{
    //citire din input.txt
    FILE *input = fopen("input.txt", "rt");
	if (input == NULL) printf("ERROR: Can't open file input.txt\n");
	readInput(input);
	fclose(input);

	//citire din captcha.bmp
	FILE *captcha = fopen(image, "rb");
	if(captcha == NULL) printf("ERROR: Can't open file captcha\n");
	readCaptcha(captcha);

	name();

    //task1

	FILE *newCaptcha = fopen(task1, "wb");
	if(newCaptcha == NULL) printf("ERROR: Can't open file newCaptcha\n");
	newColor(image, newCaptcha);
	fclose(newCaptcha);
    fclose(captcha);

    //task2
    templates(templ);
    FILE *numbers = fopen(task2, "wt");
    pixelMatrix();
    writeDigits(numbers);
    fclose(numbers);

    //task3
	FILE *fewer = fopen(task3, "wb");
	if(fewer == NULL) printf("ERROR: Can't open file fewer\n");
    delDigit(fewer);
    fclose(fewer);

	return 0;
}
