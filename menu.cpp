#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>

// ==================== PROTOTIPOS DE FUNCIONES ====================
void Pantalla();
void Memoria();

// ==================== FUNCIONES INT 10h (PANTALLA) ====================
// (Las funciones de INT 10h estaban mayormente correctas y se mantienen igual)
// ... [El código de las funciones usar_int10h_* va aquí, sin cambios] ...
#pragma region Funciones_INT10H
void usar_int10h_00h() {
    asm {
        mov ah, 0x03
        mov al, 0x03
        int 0x10
    }
    printf("\n[00h] Modo texto 80x25 activado\n");
}

void usar_int10h_01h() {
    unsigned char inicio, fin;
    printf("\n--- Configurar cursor [01h] ---");
    printf("\nLinea inicio (0-31): ");
    scanf("%hhu", &inicio);
    printf("Linea fin (0-31): ");
    scanf("%hhu", &fin);
    
    asm {
        mov ah, 0x01
        mov ch, inicio
        mov cl, fin
        int 0x10
    }
    printf("\nCursor configurado: Inicio=%d, Fin=%d\n", inicio, fin);
}

void usar_int10h_02h_03h() {
    unsigned char fila, columna;
    printf("\n--- Mover cursor [02h] ---");
    printf("\nFila (0-24): ");
    scanf("%hhu", &fila);
    printf("Columna (0-79): ");
    scanf("%hhu", &columna);
    
    asm {
        mov ah, 0x02
        mov bh, 0x00
        mov dh, fila
        mov dl, columna
        int 0x10

        mov ah, 0x03
        mov bh, 0x00
        int 0x10
        // Resultados: DH=fila, DL=columna
    }
    printf("\nCursor movido a (%d,%d)\n", fila, columna);
}

void usar_int10h_04h() {
    unsigned char inicio, fin;
    asm {
        mov ah, 0x04
        int 0x10
        mov inicio, ch
        mov fin, cl
    }
    printf("\n[04h] Forma del cursor: Inicio=%d, Fin=%d\n", inicio, fin);
}

void usar_int10h_05h() {
    unsigned char pagina;
    printf("\n--- Seleccionar pagina [05h] ---");
    printf("\nPagina (0-7): ");
    scanf("%hhu", &pagina);
    
    asm {
        mov ah, 0x05
        mov al, pagina
        int 0x10
    }
    printf("\nPagina activa cambiada a: %d\n", pagina);
}

void usar_int10h_06h() {
    asm {
        mov ah, 0x06
        mov al, 1
        mov bh, 0x17  // Fondo azul, texto blanco
        mov ch, 5     // Fila inicio
        mov cl, 10    // Col inicio
        mov dh, 15    // Fila fin
        mov dl, 70    // Col fin
        int 0x10
    }
    printf("\n[06h] Ventana desplazada hacia arriba (5,10 a 15,70)\n");
}

void usar_int10h_07h() {
    asm {
        mov ah, 0x07
        mov al, 1
        mov bh, 0x27  // Fondo verde, texto blanco
        mov ch, 5
        mov cl, 10
        mov dh, 15
        mov dl, 70
        int 0x10
    }
    printf("\n[07h] Ventana desplazada hacia abajo (5,10 a 15,70)\n");
}

void usar_int10h_08h() {
    unsigned char caracter, atributo;
    asm {
        mov ah, 0x08
        mov bh, 0x00
        int 0x10
        mov caracter, al
        mov atributo, ah
    }
    printf("\n[08h] Caracter en cursor: '%c' (0x%02X)\n", caracter, caracter);
    printf("Atributo: 0x%02X\n", atributo);
}

void usar_int10h_09h() {
    char c;
    int repeticiones;
    unsigned char color;
    printf("\n--- Escribir caracter [09h] ---");
    printf("\nCaracter: ");
    c = getche();
    printf("\nRepeticiones: ");
    scanf("%d", &repeticiones);
    printf("Color (hex 00-FF): ");
    scanf("%hhx", &color);

    
    asm {

        mov ah, 0x09
        mov al, c
        mov bh, 0x00
        mov bl, color
        mov cx, repeticiones
        int 0x10
    }
    printf("\nEscritos %d caracteres '%c' con color 0x%02X\n", repeticiones, c, color);
}

void usar_int10h_0Ah() {
    char c;
    int repeticiones;
    
    printf("\n--- Escribir caracter [0Ah] ---");
    printf("\nCaracter: ");
    c = getche();
    printf("\nRepeticiones: ");
    scanf("%d", &repeticiones);
    
    asm {
        mov ah, 0x0A
        mov al, c
        mov bh, 0x00
        mov cx, repeticiones
        int 0x10
    }
    printf("\nEscritos %d caracteres '%c'\n", repeticiones, c);
}

void usar_int10h_0Bh() {
    unsigned char tipo, valor;
    
    printf("\n--- Configurar paleta [0Bh] ---");
    printf("\nTipo (0=Borde, 1=Paleta): ");
    scanf("%hhu", &tipo);
    printf("Valor: ");
    scanf("%hhu", &valor);
    
    asm {
        mov ah, 0x0B
        mov bh, tipo
        mov bl, valor
        int 0x10
    }
    printf("\nConfiguracion aplicada: BH=%d, BL=%d\n", tipo, valor);
}

void usar_int10h_0Ch() {
    int x, y, color;
    
    asm {
        mov ax, 0x0013
        int 0x10
    }
    
    printf("\n--- Dibujar pixel [0Ch] ---");
    printf("\nCoordenada X (0-319): ");
    scanf("%d", &x);
    printf("Coordenada Y (0-199): ");
    scanf("%d", &y);
    printf("Color (0-255): ");
    scanf("%d", &color);
    
    asm {
        mov ah, 0x0C
        mov al, byte ptr color
        mov cx, x
        mov dx, y
        int 0x10
    }
    
    printf("\nPixel dibujado en (%d,%d) color %d", x, y, color);
    printf("\nPresione una tecla para continuar...");
    getch();
    
    asm {
        mov ax, 0x0003
        int 0x10
    }
}

void usar_int10h_0Dh() {
    int x, y;
    unsigned char color;
    
    asm {
        mov ax, 0x0013
        int 0x10
    }
    
    printf("\n--- Leer pixel [0Dh] ---");
    printf("\nCoordenada X (0-319): ");
    scanf("%d", &x);
    printf("Coordenada Y (0-199): ");
    scanf("%d", &y);
    
    asm {
        mov ah, 0x0D
        mov cx, x
        mov dx, y
        int 0x10
        mov color, al
    }
    
    printf("\nColor en (%d,%d): %d (0x%02X)", x, y, color, color);
    printf("\nPresione una tecla para continuar...");
    getch();
    
    asm {
        mov ax, 0x0003
        int 0x10
    }
}

void usar_int10h_0Eh() {
    char c;
    printf("\n--- Escribir TTY [0Eh] ---");
    printf("\nCaracter: ");
    c = getche();
    
    asm {
        mov ah, 0x0E
        mov al, c
        int 0x10
    }
    printf("\nCaracter '%c' enviado a TTY\n", c);
}

void usar_int10h_0Fh() {
    unsigned char modo, columnas, pagina;
    asm {
        mov ah, 0x0F
        int 0x10
        mov modo, al
        mov columnas, ah
        mov pagina, bh
    }
    printf("\n[0Fh] Modo actual: 0x%02X", modo);
    printf("\nColumnas: %d, Pagina: %d\n", columnas, pagina);
}

void usar_int10h_11h() {
    unsigned char subfuncion;
    printf("\n--- Cambiar fuente [11h] ---");
    printf("\nSubfuncion (0-3): ");
    scanf("%hhu", &subfuncion);
    
    asm {
        mov ax, 0x1100
        mov al, subfuncion
        mov bl, 0x00
        int 0x10
    }
    printf("\nFuente cambiada (subf %d)\n", subfuncion);
}

void usar_int10h_12h() {
    unsigned char subfuncion;
    unsigned short resultado;
    
    printf("\n--- Informacion extendida [12h] ---");
    printf("\nSubfuncion (0-3): ");
    scanf("%hhu", &subfuncion);
    
    asm {
        mov ax, 0x1200
        mov bl, subfuncion
        int 0x10
        mov resultado, bx
    }
    printf("\nResultado: 0x%04X\n", resultado);
}

void usar_int10h_13h() {
    char mensaje[50];
    unsigned char fila, columna, atributo;
    
    printf("\n--- Escribir cadena [13h] ---");
    printf("\nMensaje (max 49): ");
    scanf(" %[^\n]", mensaje);
    printf("Fila (0-24): ");
    scanf("%hhu", &fila);
    printf("Columna (0-79): ");
    scanf("%hhu", &columna);
    printf("Atributo (hex): ");
    scanf("%hhx", &atributo);
    
    unsigned int len = strlen(mensaje);
    
    asm {
        push es
        push ds
        pop es
        mov ah, 0x13
        mov al, 0x01
        mov bh, 0x00
        mov bl, atributo
        mov cx, len
        mov dh, fila
        mov dl, columna
        lea bp, mensaje
        int 0x10
        pop es
    }
    printf("\nCadena escrita en (%d,%d)\n", fila, columna);
}

void usar_int10h_4F02h() {
    unsigned short modo;
    printf("\n--- Modo VESA [4F02h] ---");
    printf("\nModo (ej. 0x103=800x600): ");
    scanf("%hx", &modo);
    
    unsigned short estado;
    asm {
        mov ax, 0x4F02
        mov bx, modo
        int 0x10
        mov estado, ax
    }
    
    if(estado == 0x004F) {
        printf("\nModo 0x%04X activado", modo);
    } else {
        printf("\nError: 0x%04X", estado);
    }
    
    printf("\nPresione una tecla para continuar...");
    getch();
    
    asm {
        mov ax, 0x0003
        int 0x10
    }
}
#pragma endregion

// ==================== ESTRUCTURAS Y BUFFERS GLOBALES ====================

#pragma pack(push, 1)
struct DAP {
    unsigned char size;
    unsigned char unused;
    unsigned short count;
    unsigned short offset;
    unsigned short segment;
    unsigned long long lba;
};
#pragma pack(pop)

unsigned char disk_buffer[1024] = {0};

// ==================== FUNCIONES INT 13h (DISCO) ====================

// CORRECCIÓN: Implementada la función 00h que faltaba en el switch.


void usar_int13h_01h() {
    unsigned char unidad;
    printf("\n--- Comprobar estado del disco [01h] ---");
    printf("\nUnidad (0x80=HDD1): ");
    scanf("%hhx", &unidad);
    
    unsigned char estado;
    asm {
        mov ah, 0x01
        mov dl, unidad
        int 0x13
        mov estado, ah
    }
    
    if(estado == 0) {
        printf("\nEstado: OK\n");
    } else {
        printf("\nEstado de error: 0x%02X\n", estado);
    }
}

void usar_int13h_02h() {
    unsigned char unidad, cabeza, sector, num_sectores;
    unsigned short cilindro;
    
    printf("\n--- Leer sectores CHS [02h] ---");
    printf("\nUnidad (0x80=HDD1): "); scanf("%hhx", &unidad);
    printf("Cabeza (0-15): "); scanf("%hhu", &cabeza);
    printf("Cilindro (0-1023): "); scanf("%hu", &cilindro);
    printf("Sector inicial (1-63): "); scanf("%hhu", &sector);
    printf("N° de sectores (1-127): "); scanf("%hhu", &num_sectores);
    
    unsigned char ch_reg = (unsigned char)(cilindro & 0xFF);
    unsigned char cl_reg = sector | (unsigned char)((cilindro >> 2) & 0xC0);
    unsigned char resultado, sectores_leidos;
    
    asm {
        mov ah, 0x02
        mov al, num_sectores
        mov ch, ch_reg
        mov cl, cl_reg
        mov dh, cabeza
        mov dl, unidad
        push ds
        pop es
        mov bx, offset disk_buffer
        int 0x13
        jc error_02h
    }
    resultado = 0;
    goto fin_02h;
error_02h:
    asm { mov resultado, ah }
fin_02h:
    asm { mov sectores_leidos, al }
    
    if(resultado == 0) {
        printf("\n%d sectores leídos exitosamente!\n", sectores_leidos);
        printf("Primeros 16 bytes:\n");
        for(int i = 0; i < 16; i++) {
            printf("%02X ", disk_buffer[i]);
            if(i == 7) printf(" ");
        }
        printf("\n");
    } else {
        printf("\nError en lectura: 0x%02X\n", resultado);
    }
}



void usar_int13h_04h() {
    unsigned char unidad, cabeza, sector, num_sectores;
    unsigned short cilindro;
    
    printf("\n--- Verificar sectores [04h] ---");
    printf("\nUnidad (0x80=HDD1): "); scanf("%hhx", &unidad);
    printf("Cabeza (0-15): "); scanf("%hhu", &cabeza);
    printf("Cilindro (0-1023): "); scanf("%hu", &cilindro);
    printf("Sector inicial (1-63): "); scanf("%hhu", &sector);
    printf("N° de sectores (1-127): "); scanf("%hhu", &num_sectores);

    unsigned char ch_reg = (unsigned char)(cilindro & 0xFF);
    unsigned char cl_reg = sector | (unsigned char)((cilindro >> 2) & 0xC0);
    unsigned char resultado, sectores_verificados;
    
    asm {
        mov ah, 0x04
        mov al, num_sectores
        mov ch, ch_reg
        mov cl, cl_reg
        mov dh, cabeza
        mov dl, unidad
        int 0x13
        jc error_04h
    }
    resultado = 0;
    goto fin_04h;
error_04h:
    asm { mov resultado, ah }
fin_04h:
    asm { mov sectores_verificados, al }
    
    if(resultado == 0) {
        printf("\n%d sectores verificados correctamente!\n", sectores_verificados);
    } else {
        printf("\nError en verificación: 0x%02X\n", resultado);
    }
}

void usar_int13h_08h() {
    unsigned char unidad;
    printf("\n--- Obtener parámetros unidad [08h] ---");
    printf("\nUnidad (0x00=FDD1, 0x80=HDD1): ");
    scanf("%hhx", &unidad);
    
    unsigned char max_cabezas, max_sectores, unidades_detectadas, resultado;
    unsigned short max_cilindros;
    
    asm {
        mov ah, 0x08
        mov dl, unidad
        int 0x13
        jc error_08h
    }
    resultado = 0;
    goto fin_08h;
error_08h:
    asm { mov resultado, ah }
fin_08h:
    asm {
        mov max_cabezas, dh
        mov unidades_detectadas, dl
        xor ax, ax
        mov al, cl
        and al, 0xC0
        shr al, 6
        mov ah, al
        mov al, ch
        mov max_cilindros, ax
        inc max_cilindros
        mov al, cl
        and al, 0x3F
        mov max_sectores, al
    }
    
    if(resultado == 0) {
        printf("\nParámetros de la unidad:");
        printf("\nMáximo Cilindro: %u", max_cilindros);
        printf("\nMáxima Cabeza: %u", max_cabezas + 1);
        printf("\nSectores por Pista: %u", max_sectores);
        printf("\nUnidades detectadas: %u\n", unidades_detectadas);
    } else {
        printf("\nError: 0x%02X\n", resultado);
    }
}


// ... [El resto de funciones de INT 13h (41h, 42h, etc.) estaban bien y se mantienen] ...
#pragma region Funciones_INT13H_Avanzadas
void usar_int13h_41h() {
    unsigned char unidad;
    printf("\n--- Comprobar extensiones [41h] ---");
    printf("\nUnidad (0x80=HDD1): ");
    scanf("%hhx", &unidad);
    
    unsigned short bx_val, cx_val;
    unsigned char resultado;
    
    asm {
        mov ah, 0x41
        mov bx, 0x55AA
        mov dl, unidad
        int 0x13
        jc error_41h
    }
    resultado = 0;
    goto fin_41h;
error_41h:
    asm { mov resultado, ah }
fin_41h:
    asm {
        mov bx_val, bx
        mov cx_val, cx
    }
    
    if(resultado == 0 && bx_val == 0xAA55) {
        printf("\nExtensiones soportadas! BX=0x%04X, CX=0x%04X\n", bx_val, cx_val);
        printf("Soporte para: ");
        if(cx_val & 1) printf("EDD ");
        if(cx_val & 2) printf("Enhanced Disk Drive ");
        if(cx_val & 4) printf("ATA Lock/Unlock ");
        printf("\n");
    } else {
        printf("\nExtensiones NO soportadas o error: 0x%02X\n", resultado);
    }
}

void usar_int13h_42h() {
    unsigned char unidad;
    unsigned long long lba;
    unsigned short num_sectores;
    
    printf("\n--- Leer sectores LBA [42h] ---");
    printf("\nUnidad (0x80=HDD1): ");
    scanf("%hhx", &unidad);
    printf("Dirección LBA: ");
    scanf("%llu", &lba);
    printf("N° sectores (1-127): ");
    scanf("%hu", &num_sectores);
    
    struct DAP dap;
    dap.size = sizeof(dap);
    dap.unused = 0;
    dap.count = num_sectores;
    dap.offset = FP_OFF(disk_buffer);
    dap.segment = FP_SEG(disk_buffer);
    dap.lba = lba;
    
    unsigned char resultado;
    unsigned int seg_dap = FP_SEG(&dap);
    unsigned int off_dap = FP_OFF(&dap);
    
    asm {
        push ds
        mov ax, seg_dap
        mov ds, ax
        mov ah, 0x42
        mov dl, unidad
        mov si, off_dap
        int 0x13
        pop ds
        jc error_42h
    }
    resultado = 0;
    goto fin_42h;
error_42h:
    asm { mov resultado, ah }
fin_42h:
    if(resultado == 0) {
        printf("\n%d sectores leídos exitosamente!\n", num_sectores);
        printf("Primeros 16 bytes:\n");
        for(int i = 0; i < 16; i++) {
            printf("%02X ", disk_buffer[i]);
            if(i == 7) printf(" ");
        }
        printf("\n");
    } else {
        printf("\nError: 0x%02X\n", resultado);
    }
}


void usar_int13h_43h() {
    unsigned char unidad;
    unsigned long long lba;
    unsigned short num_sectores;
    
    printf("\n--- Escribir sectores LBA [43h] ---");
    printf("\nADVERTENCIA: Operación peligrosa!");
    printf("\n¿Continuar? (s/n): ");
    if(getche() != 's') return;
    
    printf("\nUnidad (0x80=HDD1): "); scanf("%hhx", &unidad);
    printf("Dirección LBA: "); scanf("%llu", &lba);
    printf("N° sectores (1-127): "); scanf("%hu", &num_sectores);
    
    for(int i = 0; i < sizeof(disk_buffer); i++) { disk_buffer[i] = 0xAA; }
    
    struct DAP dap;
    dap.size = sizeof(dap);
    dap.unused = 0;
    dap.count = num_sectores;
    dap.offset = FP_OFF(disk_buffer);
    dap.segment = FP_SEG(disk_buffer);
    dap.lba = lba;
    
    unsigned char resultado;
    unsigned int seg_dap = FP_SEG(&dap);
    unsigned int off_dap = FP_OFF(&dap);
    
    asm {
        push ds
        mov ax, seg_dap
        mov ds, ax
        mov ah, 0x43
        mov dl, unidad
        mov si, off_dap
        int 0x13
        pop ds
        jc error_43h
    }
    resultado = 0;
    goto fin_43h;
error_43h:
    asm { mov resultado, ah }
fin_43h:
    if(resultado == 0) {
        printf("\n%d sectores escritos exitosamente!\n", num_sectores);
    } else {
        printf("\nError: 0x%02X\n", resultado);
    }
}

void usar_int13h_48h() {
    unsigned char unidad;
    printf("\n--- Obtener capacidad disco [48h] ---");
    printf("\nUnidad (0x80=HDD1): ");
    scanf("%hhx", &unidad);
    
    #pragma pack(push, 1)
    struct DiskCapacity {
        unsigned short size;
        unsigned short flags;
        unsigned long cylinders;
        unsigned long heads;
        unsigned long sectors_per_track;
        unsigned long long total_sectors;
        unsigned short bytes_per_sector;
    } capacity = {0};
    #pragma pack(pop)
    
    capacity.size = sizeof(capacity);
    
    unsigned char resultado;
    unsigned int seg_cap = FP_SEG(&capacity);
    unsigned int off_cap = FP_OFF(&capacity);
    
    asm {
        push ds
        mov ax, seg_cap
        mov ds, ax
        mov ah, 0x48
        mov dl, unidad
        mov si, off_cap
        int 0x13
        pop ds
        jc error_48h
    }
    resultado = 0;
    goto fin_48h;
error_48h:
    asm { mov resultado, ah }
fin_48h:
    if(resultado == 0) {
        // La estructura "capacity" se llena por la interrupción
        printf("\nCapacidad del disco:");
        printf("\nCilindros: %lu", capacity.cylinders);
        printf("\nCabezas: %lu", capacity.heads);
        printf("\nSectores por pista: %lu", capacity.sectors_per_track);
        printf("\nSectores totales: %llu", capacity.total_sectors);
        printf("\nBytes por sector: %u", capacity.bytes_per_sector);
        
        if(capacity.bytes_per_sector > 0) {
            unsigned long long total_bytes = capacity.total_sectors * capacity.bytes_per_sector;
            printf("\nCapacidad total: %.2f MB", total_bytes / (1024.0 * 1024.0));
        }
        printf("\n");
    } else {
        printf("\nError: 0x%02X\n", resultado);
    }
}
#pragma endregion

// ==================== MENÚS Y FUNCIÓN PRINCIPAL ====================

void mouse() {   
    printf("en desarrollo\n");
}

void impresora() {
    printf("en desarrollo\n");
}  

int main() {
    int opcion;
    do {
        system("cls");
        printf("\n----- MENU PRINCIPAL -----\n");
        printf("1. Mouse\n");
        printf("2. Impresora\n");
        printf("3. Pantalla\n");
        printf("4. Disco (Memoria masiva)\n");
        printf("5. Salir\n");
        printf("Selecciona una opcion: ");
        
        if (scanf("%d", &opcion) != 1) {
            opcion = 99; // Opción inválida por defecto
            while(getchar() != '\n'); // Limpiar buffer de entrada
        }

        switch (opcion) {
            case 1: mouse(); break;
            case 2: impresora(); break;
            case 3: Pantalla(); break;
            case 4: Memoria(); break;
            case 5: printf("Saliendo...\n"); break;
            default: printf("Opcion invalida.\n");
        }

        if (opcion != 5) {
            printf("\nPresiona una tecla para continuar...");
            getch();
        }

    } while (opcion != 5);

    return 0;
}

void Pantalla() {
    int opcionPantalla;
    do {
        system("cls");
        printf("=== SUBMENU - INT 10h (Pantalla) ===\n");
        printf("1. Establecer modo de video (00h)\n");
        printf("2. Establecer forma del cursor (01h)\n");
        printf("3. Mover y leer cursor (02h + 03h)\n");
        printf("4. Leer forma del cursor (04h)\n");
        printf("5. Seleccionar pagina activa (05h)\n");
        printf("6. Scroll arriba (06h)\n");
        printf("7. Scroll abajo (07h)\n");
        printf("8. Leer caracter en cursor (08h)\n");
        printf("9. Escribir caracter repetido (09h)\n");
        printf("10. Escribir sin mover cursor (0Ah)\n");
        printf("11. Cambiar paleta (0Bh)\n");
        printf("12. Escribir pixel (0Ch)\n");
        printf("13. Leer pixel (0Dh)\n");
        printf("14. TTY (0Eh)\n");
        printf("15. Leer modo actual (0Fh)\n");
        printf("16. Cambiar fuente (11h)\n");
        printf("17. Leer info extendida (12h)\n");
        printf("18. Escribir cadena (13h)\n");
        printf("19. Establecer modo VESA (4F02h)\n");
        printf("0. Volver al menu principal\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcionPantalla);

        switch (opcionPantalla) {
            case 1: usar_int10h_00h(); break;
            case 2: usar_int10h_01h(); break;
            case 3: usar_int10h_02h_03h(); break;
            case 4: usar_int10h_04h(); break;
            case 5: usar_int10h_05h(); break;
            case 6: usar_int10h_06h(); break;
            case 7: usar_int10h_07h(); break;
            case 8: usar_int10h_08h(); break;
            case 9: usar_int10h_09h(); break;
            case 10: usar_int10h_0Ah(); break;
            case 11: usar_int10h_0Bh(); break;
            case 12: usar_int10h_0Ch(); break;
            case 13: usar_int10h_0Dh(); break;
            case 14: usar_int10h_0Eh(); break;
            case 15: usar_int10h_0Fh(); break;
            case 16: usar_int10h_11h(); break;
            case 17: usar_int10h_12h(); break;
            case 18: usar_int10h_13h(); break;
            case 19: usar_int10h_4F02h(); break;
            case 0: return;
            default: printf("Opcion invalida.\n"); break;
        }

        printf("\nPresiona cualquier tecla para continuar...");
        getch();
    } while (opcionPantalla != 0);
}

void Memoria() {
    int opcionMemoria;
    do {
        system("cls");
        printf("=== SUBMENU - INT 13h (Disco) ===\n");
        // CORRECCIÓN: Menú actualizado para reflejar las funciones implementadas.

        printf(" 1. Comprobar estado disco (01h)\n");
        printf(" 2. Leer sectores CHS (02h)\n");
        printf(" 3. Verificar sectores (04h)\n");
        printf(" 4. Obtener parametros unidad (08h)\n");
        printf(" 5. Comprobar extensiones (41h)\n");
        printf(" 6. Leer sectores LBA (42h)\n");
        printf(" 7. Escribir sectores LBA (43h)\n");
        printf(" 8. Obtener capacidad disco (48h)\n");
        printf(" 0. Volver al menu principal\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcionMemoria);

        // CORRECCIÓN: Switch completado con todas las opciones.
        switch (opcionMemoria) {

            case 1: usar_int13h_01h(); break;
            case 2: usar_int13h_02h(); break;
            case 3: usar_int13h_04h(); break;
            case 4: usar_int13h_08h(); break;
            case 5: usar_int13h_41h(); break;
            case 6: usar_int13h_42h(); break;
            case 7: usar_int13h_43h(); break;
            case 8: usar_int13h_48h(); break;
            case 0: 
                printf("\nVolviendo al menu principal...\n");
                break; // Se prepara para salir del bucle
            default:
                printf("Opcion invalida.\n");
                break;
        }

        printf("\nPresiona cualquier tecla para continuar...");
        getch();
    } while (opcionMemoria != 0);
}

// CORRECCIÓN: Se eliminó la llave '}' extra que estaba al final del archivo original.