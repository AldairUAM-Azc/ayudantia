#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LON_NOMBRE 10

struct Registro {
    int matricula;
    char nombre[MAX_LON_NOMBRE];
    char apellido[MAX_LON_NOMBRE];
    int edad;
};

void leer_registros();
struct Registro* crear_registro(int matricula, char* nombre, char* apellido,
                                int edad);
void imprimir_registros(struct Registro* regs[], int total);
void imprimir_registro(struct Registro* r);
void imprimir_mayores_de_edad(struct Registro* regs[], int total);
void limpiar_registros(struct Registro* regs[], int total);
void limpiar_registro(struct Registro* r);

int main() {
    leer_registros();
    return 0;
};

void leer_registros() {
    int num_registros;
    int matricula, edad;
    char nombre[MAX_LON_NOMBRE];
    char apellido[MAX_LON_NOMBRE];
    printf("Leyendo los registro del archivo ...\n\n");
    FILE* registros_file = fopen("datos_original.txt", "r");
    fscanf(registros_file, "%d", &num_registros);
    struct Registro* registros[num_registros];
    for (int i = 0; i < num_registros; i++) {
        fscanf(registros_file, "%d %s %s %d", &matricula, &nombre[0],
               &apellido[0], &edad);
        struct Registro* registro =
            crear_registro(matricula, &nombre[0], &apellido[0], edad);
        registros[i] = registro;
    }
    fclose(registros_file);

    printf("Imprimiendo los registros leidos:\n\n");
    imprimir_registros(registros, num_registros);
    printf("\nImprimiendo los registros de alumnos mayores de edad:\n\n");
    imprimir_mayores_de_edad(registros, num_registros);
    printf("\nLimpiando la memoria...\n");
    limpiar_registros(registros, num_registros);
    printf("Fin de ejecucion\n");
}

void imprimir_mayores_de_edad(struct Registro* regs[], int total) {
    for (int i = 0; i < total; i++) {
        if (regs[i]->edad >= 18) {
            imprimir_registro(regs[i]);
        }
    }
}

struct Registro* crear_registro(int matricula, char* nombre, char* apellido,
                                int edad) {
    struct Registro* registro =
        (struct Registro*)malloc(sizeof(struct Registro));
    registro->matricula = matricula;
    registro->edad = edad;
    strncpy(registro->nombre, nombre, MAX_LON_NOMBRE);
    strncpy(registro->apellido, apellido, MAX_LON_NOMBRE);
    return registro;
}

void limpiar_registros(struct Registro* regs[], int total) {
    for (int i = 0; i < total; i++) {
        limpiar_registro(regs[i]);
    }
}

void limpiar_registro(struct Registro* r) { free(r); }

void imprimir_registros(struct Registro* regs[], int total) {
    printf("Matricula | Nombre | Apellido | Edad\n");
    for (int i = 0; i < total; i++) {
        imprimir_registro(regs[i]);
    }
}
void imprimir_registro(struct Registro* r) {
    printf("%d | %s | %s | %d\n", r->matricula, r->nombre, r->apellido,
           r->edad);
}