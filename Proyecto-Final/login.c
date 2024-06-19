#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char usuario[50];
    char contrasenia[50];
} Usuario;

void menuLogin()
{
    char archivoUsuarios[50] = "usuarios.bin";

    int opcion;
    printf("Elegir una opcion\n");
    printf("1. Conectarse\n");
    printf("2. Registrarse\n");
    scanf("%i", &opcion);

    system("cls");

    switch(opcion)
    {
    case 1:
    {
        int flag;
        flag = login(archivoUsuarios);
        if(flag == 0)
        {
            printf("user");
            /// menuUsuario(); CREAR MENU USUARIO
        }
        else
        {
            printf("admin");
            ///  menuAdmin(); CREAR MENU ADMIN
        }

        break;
    }

    case 2:
    {
        registrarse(archivoUsuarios);
        menuLogin();
        break;
    }

    default:
        printf("Opcion incorrecta =(\n");
    }
}

int login(char nombreArchivo[])
{
    FILE *archi = fopen(nombreArchivo, "rb");
    int i = 0;


    if(archi != NULL)
    {
        char usuarioTemp[50];
        char contraseniaTemp[50];
        int flag = 0;

        do
        {
            printf("Ingrese su usuario\n");
            fflush(stdin);
            gets(usuarioTemp);

            printf("Ingrese su contrasenia\n");
            fflush(stdin);
            gets(contraseniaTemp);

            Usuario a;

            while(fread(&a, sizeof(Usuario), 1, archi))
            {
                /// Comprobar si logeo el admin
                if(strcmp(usuarioTemp, "admin") == 0 && strcmp(contraseniaTemp, "admin") == 0)
                {
                    flag = 1;
                    i = 1;
                    break;
                }

                /// Comprobar si logeo un usuario
                if(strcmp(a.usuario, usuarioTemp) == 0 && strcmp(a.contrasenia, contraseniaTemp) == 0)
                {
                    flag = 1;
                    break;
                }
            }

            if(flag == 0)
            {
                printf("Datos invalidos =(\n");
                fseek(archi, 0, SEEK_SET);
                sleep(1);
                system("cls");
            }

        }
        while(flag == 0);

        fclose(archi);

        if(i == 1)
        {
            printf("Espere un momento...\n");
            sleep(2);
            system("cls");
            return i;
        }

        printf("Espere un momento...\n");
        sleep(2);
        system("cls");
        return i;
    }
    else
    {
        printf("No se puede leer el archivo =(\n");
    }
}

void registrarse(char nombreArchivo[])
{

    FILE *archi = fopen(nombreArchivo, "ab");

    if(archi != NULL)
    {
        Usuario a;

        printf("----- Registro -----");

        printf("\nIngrese usuario\n");
        fflush(stdin);
        gets(a.usuario);

        printf("Ingrese contrasenia\n");
        fflush(stdin);
        gets(a.contrasenia);

        fwrite(&a, sizeof(Usuario), 1, archi);

        fclose(archi);

        printf("Usuario creado con exito =) \n");
        printf("Espere un momento...\n");
        sleep(2);
        system("cls");
    }

}

