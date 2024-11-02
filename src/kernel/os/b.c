#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CACHE_FILE "cache.txt"


void crashedKernel() {
    printk("Opppss.... The program has crashed / This could be a computer or Kernel bug, if the problem exists, please go to the official website to report the error.",0);
    printk("             CabimOS : v0.0.1 (BETA) : Bug Not Normal. ",1);
}

// Función para guardar datos en caché
void save_to_cache(const char* key, const char* value) {
    FILE* file = fopen(CACHE_FILE, "a"); // Abrir el archivo en modo append
    if (file == NULL) {
        printk("error cache open / crashed os",0);
        return;
    }
    fprintf(file, "%s=%s\n", key, value); // Guardar clave y valor
    fclose(file);
}

const char* get_from_cache(const char* key) {
    static char value[50];
    FILE* file = fopen(CACHE_FILE, "r"); // Abrir el archivo en modo lectura
    if (file == NULL) {
        printk("error cache open / crashed os",0);
        return NULL;
    }

    while (fscanf(file, "%49[^=]=%49[^\n]\n", key, value) == 2) {
        if (strcmp(key, key) == 0) {
            fclose(file);
            printk("Error: data a exist", 1); // Mensaje de error
            return value; // Retornar el valor encontrado
        }
    }
    fclose(file);
    return NULL; // No encontrado
}

void delete_from_cache(const char* key) {
    FILE* file = fopen(CACHE_FILE, "r"); // Abrir el archivo en modo lectura
    if (file == NULL) {
        printk("error cache open / crashed os",0);
        return;
    }

    FILE* temp_file = fopen("temp_cache.txt", "w"); // Crear un archivo temporal
    if (temp_file == NULL) {
        fclose(file);
        printk("error creating temp file / crashed os",0);
        return;
    }

    char line[100];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, key, strlen(key)) != 0) {
            fputs(line, temp_file); // Escribir en el archivo temporal si no es la clave a eliminar
        } else {
            found = 1; // Se encontró la clave a eliminar
        }
    }

    fclose(file);
    fclose(temp_file);

    if (found) {
        remove(CACHE_FILE); // Eliminar el archivo original
        rename("temp_cache.txt", CACHE_FILE); // Renombrar el archivo temporal
        printk("a user deleted!", 0); // Mensaje de éxito
    } else {
        remove("temp_cache.txt"); // Eliminar el archivo temporal si no se encontró la clave
        printk("Error: user not found", 0); // Mensaje de error
    }
}

/*
int main() {
    save_to_cache("usuario1", "datos1");
    const char* value = get_from_cache("usuario1");
    if (value) {
        printf("Valor encontrado en caché: %s\n", value);
    } else {
        printf("Valor no encontrado en caché.\n");
    }
    return 0;
}*/