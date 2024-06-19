#include "EasyPIO.h"
extern void cargando_arm();
extern void radar_arm();

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <fcntl.h>

const char LEDS[8] = {7, 8, 25, 24, 23, 18, 15, 14}; // Puertos de raspberry

int VELOCIDAD_AUTO_FANTASTICO = 200;
int VELOCIDAD_EL_CHOQUE = 200;
int VELOCIDAD_CARGANDO = 200;
int VELOCIDAD_RADAR = 200;
    
void disp_binary(int);
int leds(int);
char getchi();
char menu();
int kbhit();
void autoFantastico();
void elChoque();
void Cargando();
void delay(int);
void Radar();
struct termios disable_echo();
void enable_echo();
size_t write_callback(char *, size_t, size_t, void *);
long long int getChatId();

int main()
{
    pioInit();
    int i;
    for (i = 0; i < 8; i++)
    {
        pinMode(LEDS[i], OUTPUT); // Configure los 8 pines para los LEDs como salidas en main
    }
    leds(0xFF);

    char password[5];
    int cont = 0;
    char opc;


    while (cont < 3)
    {
        struct termios oldattr = disable_echo();

        printf("Ingrese su password de 5 digitos: \n");
        int i = 0;
        do
        {
            password[i] = getchar();
            if (password[i] == 127)
            { // Manejo de la tecla Backspace
                if (i > 0)
                {
                    i--;
                    printf("\b \b"); // Elimina el último carácter impreso
                }
            }
            else
            {
                printf("*");
                fflush(stdout);
                i++;
            }
        } while (i < 5);

        enable_echo(oldattr);
        char correctPassword[5] = "12345";
        bool checkPas = true;
        for (int i = 0; i < 5; i++)
        {
            if (password[i] != correctPassword[i])
            {
                checkPas = false;
            }
        }

        if (checkPas)
        {
            printf("\n Bienvenido al sistema \n");
            do
            {
                printf("Ingrese la secuencia que desea ver:\n");
                printf("1. ¡Auto Fantastico!\n");
                printf("2. ¡El choque!\n");
                printf("3. ¡Cargando...!\n");
                printf("4. ¡Radar!\n");
                printf("5. Salir\n");
                printf("Opcion: ");

                // Deshabilitar el búfer de entrada de la terminal
                struct termios oldattr, newattr;
                tcgetattr(STDIN_FILENO, &oldattr);
                newattr = oldattr;
                newattr.c_lflag &= ~(ICANON | ECHO);
                tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

                // Leer el carácter ingresado
                opc = getchar();

                // Restaurar la configuración original de la terminal
                tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
                switch (opc)
                {
                case '1':
                    autoFantastico();
                    break;
                case '2':
                    elChoque();
                    break;
                case '3':
                    cargando_arm();
                    break;
                case '4':
                    radar_arm();
                    break;
                case '5':
                    printf("\n Saliendo del sistema \n");
                    break;
                default:
                    break;
                }
            } while (opc != '5');
            

            break;
        }
        else
        {
            cont = cont + 1;
            printf("%s", &password);
            printf("Password no valida \n");
        }
    }

    if (cont == 3)
    {
        printf("Supero la cantidad maxima de intentos para acceder al menu");
        return 1;
    }

}

void disp_binary(int i)
{

    for (int t = 128; t > 0; t /= 2)
    {
        if (i & t)
        {
            printf("*");
        }
        else
        {
            printf("_");
        }
    }
    printf("\n");
}

void delay(int milliseconds)
{
    unsigned long pausa;
    clock_t ahora, despues;

    pausa = milliseconds * (CLOCKS_PER_SEC / 1000);
    ahora = clock();
    despues = ahora;
    while ((ahora - despues) < pausa)
    {
        ahora = clock();
    }
}


void autoFantastico()
{
    system("clear");
    char ch;
    int i;
    while (1)
    {
        int t = 128;
        for (t; t >= 2; t /= 2)
        {
            ch = getchi();
            if (ch == 'U')
            {
                if (VELOCIDAD_AUTO_FANTASTICO >= 60)
                {
                    VELOCIDAD_AUTO_FANTASTICO -= 20;
                }
            }
            else if (ch == 'D')
            {
                if (VELOCIDAD_AUTO_FANTASTICO <= 600)
                {
                    VELOCIDAD_AUTO_FANTASTICO += 20;
                }
            }
            else if (ch == 'O')
            {
                return;
            }
            printf("Ejecutando la secuencia ¡Auto Fantastico!. Presione enter para salir\n");
            disp_binary(t);
            leds(t);
            delay(VELOCIDAD_AUTO_FANTASTICO);
            system("clear");
        }
        for (t; t < 128; t *= 2)
        {
            ch = getchi();
            if (ch == 'U')
            {
                if (VELOCIDAD_AUTO_FANTASTICO >= 60)
                {
                    VELOCIDAD_AUTO_FANTASTICO -= 20;
                }
            }
            else if (ch == 'D')
            {
                if (VELOCIDAD_AUTO_FANTASTICO <= 600)
                {
                    VELOCIDAD_AUTO_FANTASTICO += 20;
                }
            }
            else if (ch == 'O')
            {
                return;
            }
            printf("Ejecutando la secuencia ¡Auto Fantastico!. Presione enter para salir\n");
            disp_binary(t);
            leds(t);
            delay(VELOCIDAD_AUTO_FANTASTICO);
            system("clear");
        }
    }
    leds(0);
}

void elChoque()
{
    system("clear");
    int elChoque[8] = {129, 66, 36, 24, 24, 36, 66, 129};
    char ch;
    while (1)
    {
        for (int i = 0; i < 8; i++)
        {

            ch = getchi();
            if (ch == 'U')
            {
                if (VELOCIDAD_EL_CHOQUE >= 60)
                    VELOCIDAD_EL_CHOQUE -= 20;
            }
            else if (ch == 'D')
            {
                if (VELOCIDAD_EL_CHOQUE <= 600)
                    VELOCIDAD_EL_CHOQUE += 20;
            }
            else if (ch == 'O')
            {
                return;
            }
            printf("Ejecutando la secuencia ¡elChoque...!. Presione enter para salir\n");
            disp_binary(elChoque[i]);
            leds(elChoque[i]);
            delay(VELOCIDAD_EL_CHOQUE);
            system("clear");
        }
    }
    leds(0);
}

void Cargando()
{
    char ch;
    system("clear");

    while (1)
    {
        int j = 128;
        int i = 128;
        for (i; i <= 255; i = i + j)
        {
            ch = getchi();
            if (ch == 'U')
            {
                if (VELOCIDAD_CARGANDO >= 60)
                {
                    VELOCIDAD_CARGANDO -= 20;
                }
            }
            else if (ch == 'D')
            {
                if (VELOCIDAD_CARGANDO <= 600)
                {
                    VELOCIDAD_CARGANDO += 20;
                }
            }
            else if (ch == 'O')
            {
                return;
            }
            printf("Ejecutando la secuencia ¡Cargando...!. Presione enter para salir\n");
            disp_binary(i);
            leds(i);
            delay(VELOCIDAD_CARGANDO);
            system("clear");
            j /= 2;
            if (j == 0)
            {
                j = 1;
            }
        }
    };
    leds(0);
}

void Radar()
{
    unsigned int radar[8] = {128, 64, 32, 16, 24, 20, 18, 17};
    char ch;
    system("clear");

    do
    {
        while (1)
        {
            for (int i = 0; i < 8; i++)
            {
                ch = getchi();
                if (ch == 'U')
                {
                    if (VELOCIDAD_RADAR >= 60)
                        VELOCIDAD_RADAR -= 20;
                }
                else if (ch == 'D')
                {
                    if (VELOCIDAD_RADAR <= 600)
                        VELOCIDAD_RADAR += 20;
                }
                else if (ch == 'O')
                {
                    return;
                }
                printf("Ejecutando la secuencia ¡Radar...!. Presione enter para salir\n");
                disp_binary(radar[i]);
                leds(radar[i]);
                delay(VELOCIDAD_RADAR);
                system("clear");
            }
        }
    } while (1);
    leds(0);
}

struct termios disable_echo()
{
    struct termios oldattr, newattr;

    tcgetattr(STDIN_FILENO, &oldattr);

    newattr = oldattr;

    newattr.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

    return oldattr;
}

void enable_echo(struct termios oldattr)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
}

char getchi()
{
    struct termios old_term, new_term;

    // Guardar la configuración actual de la terminal
    tcgetattr(STDIN_FILENO, &old_term);

    // Configurar la terminal para leer los caracteres sin necesidad de presionar Enter
    new_term = old_term;
    new_term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    if (!kbhit())
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
        return 'N';
    }

    char ch = getchar();

    if (ch == 27) // Comprueba si el caracter es un escape
    {
        // Lee las secuencias de escape correspondientes a las flechas
        char arrow1 = getchar();
        char arrow2 = getchar();

        if (arrow1 == '[')
        {
            switch (arrow2)
            {
            case 'A':
                tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
                return 'U'; // Flecha hacia arriba

            case 'B':
                tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
                return 'D'; // Flecha hacia abajo

            case 'C':
                tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
                return 'R'; // Flecha hacia la derecha

            case 'D':
                tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
                return 'L'; // Flecha hacia la izquierda
            }
        }
    }
    else
    {
        return 'O';
    }
}

int kbhit()
{
    struct termios old_term, new_term;
    int ch;

    tcgetattr(STDIN_FILENO, &old_term);

    new_term = old_term;
    new_term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

    int old_flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, old_flags | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
    fcntl(STDIN_FILENO, F_SETFL, old_flags);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

 int leds(int num)
 {
     int i, numval;

     for (i = 0; i < 8; i++)
     {
         // Write the number to the 8 LEDs
         numval = (num >> i) & 0x01;
         digitalWrite(LEDS[i], numval);
     }

     return 0;
}

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) // Esta funcion devuelve el numero de bytes procesaoos
{                                                                           // Funcion de devolucion de llamada, que se utiliza en el contexto de operaciones
    // de transferencia de datos, como es la comunicaciones HTTP
    // calcula ek tamanio real de los datos recibidos
    size_t realsize = size * nmemb;
    char *response = (char *)userdata;
    strncat(response, ptr, realsize);
    return realsize;
}
