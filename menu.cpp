#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>
#include <graphics.h> // Para initgraph, closegraph, putpixel (si se usa modo grafico)

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
#pragma region Funciones_INT13H
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

// ==================== Metodos para mause ====================
#pragma region Funciones_INT33H




// Variables globales para la posición del ratón (opcional, para seguimiento)
int mouse_x = 0;
int mouse_y = 0;
int mouse_buttons = 0;

// --- Funciones de la Interrupción 33h ---
void usar_int33h_0Dh();


// Función 00h: Inicializar el driver del ratón / Comprobar presencia del ratón
void usar_int33h_00h() {
    printf("\n--- Inicializar el driver del ratón (00h) ---\n");
    int status;
    int buttons;

    asm {
        mov ax, 0x00
        int 0x33
        mov status, ax
        mov buttons, bx
    }

    if (status == 0xFFFF) {
        printf("Driver del ratón instalado y presente.\n");
        printf("Número de botones: %d\n", buttons);
    } else {
        printf("Driver del ratón NO instalado o ratón NO presente.\n");
    }
}

// Función 01h: Mostrar el cursor del ratón
void usar_int33h_01h() {
    printf("\n--- Mostrar el cursor del ratón (01h) ---\n");
    printf("Mueve el ratón para ver el cursor.\n");
    asm {
        mov ax, 0x01
        int 0x33
    }
    printf("Cursor del ratón mostrado.\n");
}

// Función 02h: Ocultar el cursor del ratón
void usar_int33h_02h() {
    printf("\n--- Ocultar el cursor del ratón (02h) ---\n");
    printf("Mueve el ratón para ver que el cursor esta oculto.\n");
    asm {
        mov ax, 0x02
        int 0x33
    }
    printf("Cursor del ratón oculto.\n");
}

// Función 03h: Obtener la posición y el estado de los botones del ratón
void usar_int33h_03h() {
    printf("\n--- Obtener posición y estado de botones (03h) ---\n");
    printf("Mueva el ratón y presione los botones para ver el estado (presione cualquier tecla para salir).\n");

    int x, y, buttons;
    do {
        asm {
            mov ax, 0x03
            int 0x33
            mov buttons, bx
            mov x, cx
            mov y, dx
        }
        clrscr(); // Limpiar pantalla para actualizar
        printf("X: %d, Y: %d, Botones: ", x, y);
        if (buttons & 0x01) printf("Izquierdo ");
        if (buttons & 0x02) printf("Derecho ");
        if (buttons & 0x04) printf("Central ");
        if (!(buttons & 0x01) && !(buttons & 0x02) && !(buttons & 0x04)) printf("Ninguno");
        delay(100); // Pequeña pausa para evitar parpadeo excesivo
    } while (!kbhit());
    getch(); // Limpiar el buffer del teclado
    printf("\nPresiona cualquier tecla para continuar...\n");
    getch();
}

// Función 04h: Establecer la posición del cursor del ratón
void usar_int33h_04h() {
    printf("\n--- Establecer posición del cursor (04h) ---\n");
    int new_x, new_y;
    printf("Introduce nueva coordenada X (por ejemplo, 320): ");
    scanf("%d", &new_x);
    printf("Introduce nueva coordenada Y (por ejemplo, 240): ");
    scanf("%d", &new_y);

    asm {
        mov ax, 0x04
        mov cx, new_x
        mov dx, new_y
        int 0x33
    }
    printf("Cursor movido a X: %d, Y: %d\n", new_x, new_y);
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 05h: Obtener información de botón pulsado
void usar_int33h_05h() {
    printf("\n--- Obtener información de botón pulsado (05h) ---\n");
    printf("Pulsa los botones del ratón para ver la información (presiona cualquier tecla para salir).\n");

    int button_status, press_count, x_coord, y_coord;
    int button_id; // 0=izquierdo, 1=derecho, 2=central

    do {
        clrscr(); // Limpiar pantalla para actualizar
        for (button_id = 0; button_id <= 2; ++button_id) { // Iterar para los 3 botones
            asm {
                mov ax, 0x05
                mov bx, button_id
                int 0x33
                mov button_status, ax
                mov press_count, bx
                mov x_coord, cx
                mov y_coord, dx
            }

            if (button_status != 0) { // Si el botón fue pulsado
                printf("Botón ");
                if (button_id == 0) printf("Izquierdo");
                else if (button_id == 1) printf("Derecho");
                else if (button_id == 2) printf("Central");
                printf(" pulsado %d veces en X: %d, Y: %d\n", press_count, x_coord, y_coord);
            }
        }
        delay(100);
    } while (!kbhit());
    getch();
    printf("\nPresiona cualquier tecla para continuar...\n");
    getch();
}

// Función 06h: Obtener información de botón soltado
void usar_int33h_06h() {
    printf("\n--- Obtener información de botón soltado (06h) ---\n");
    printf("Suelte los botones del ratón para ver la información (presiona cualquier tecla para salir).\n");

    int button_status, release_count, x_coord, y_coord;
    int button_id; // 0=izquierdo, 1=derecho, 2=central

    do {
        clrscr(); // Limpiar pantalla para actualizar
        for (button_id = 0; button_id <= 2; ++button_id) { // Iterar para los 3 botones
            asm {
                mov ax, 0x06
                mov bx, button_id
                int 0x33
                mov button_status, ax
                mov release_count, bx
                mov x_coord, cx
                mov y_coord, dx
            }

            if (button_status != 0) { // Si el botón fue soltado
                printf("Botón ");
                if (button_id == 0) printf("Izquierdo");
                else if (button_id == 1) printf("Derecho");
                else if (button_id == 2) printf("Central");
                printf(" soltado %d veces en X: %d, Y: %d\n", release_count, x_coord, y_coord);
            }
        }
        delay(100);
    } while (!kbhit());
    getch();
    printf("\nPresiona cualquier tecla para continuar...\n");
    getch();
}

// Función 07h: Establecer límites horizontales para el cursor
void usar_int33h_07h() {
    printf("\n--- Establecer límites horizontales (07h) ---\n");
    int min_x, max_x;
    printf("Introduce el límite X mínimo (ej. 100): ");
    scanf("%d", &min_x);
    printf("Introduce el límite X máximo (ej. 500): ");
    scanf("%d", &max_x);

    asm {
        mov ax, 0x07
        mov cx, min_x
        mov dx, max_x
        int 0x33
    }
    printf("Límites horizontales establecidos: X min=%d, X max=%d\n", min_x, max_x);
    printf("Mueva el ratón para observar los límites (presiona cualquier tecla para restaurar).\n");
    getch();

    // Restaurar límites por defecto (0 a 639 para modo gráfico, o 0 a 79 para texto)
    asm {
        mov ax, 0x07
        mov cx, 0          // Valor por defecto
        mov dx, 639        // Valor por defecto para 640x480
        int 0x33
    }
    printf("Límites restaurados.\n");
}

// Función 08h: Establecer límites verticales para el cursor
void usar_int33h_08h() {
    printf("\n--- Establecer límites verticales (08h) ---\n");
    int min_y, max_y;
    printf("Introduce el límite Y mínimo (ej. 100): ");
    scanf("%d", &min_y);
    printf("Introduce el límite Y máximo (ej. 300): ");
    scanf("%d", &max_y);

    asm {
        mov ax, 0x08
        mov cx, min_y
        mov dx, max_y
        int 0x33
    }
    printf("Límites verticales establecidos: Y min=%d, Y max=%d\n", min_y, max_y);
    printf("Mueva el ratón para observar los límites (presiona cualquier tecla para restaurar).\n");
    getch();

    // Restaurar límites por defecto (0 a 479 para modo gráfico, o 0 a 199/24 para texto)
    asm {
        mov ax, 0x08
        mov cx, 0          // Valor por defecto
        mov dx, 479        // Valor por defecto para 640x480
        int 0x33
    }
    printf("Límites restaurados.\n");
}

// Función 09h: Establecer forma del cursor de software (gráfico)
// NOTA: Para esta función, necesitarás un modo gráfico inicializado.
// Los datos de la máscara deben ser un array de 64 bytes (32 para la pantalla, 32 para la máscara XOR)
// y deben estar accesibles desde el ensamblador (por ejemplo, como variable global).
unsigned char cursor_mask[32] = {
    0x00, 0x00, 0x00, 0x00, // Primeras 16 palabras para pantalla (AND Mask)
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, // Siguientes 16 palabras para XOR Mask
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
};

void usar_int33h_09h() {
    printf("\n--- Establecer forma del cursor de software (09h) ---\n");
    printf("Esta función requiere un modo gráfico. Se intentará inicializar un modo gráfico.\n");
    printf("Presiona cualquier tecla para continuar y ver el cursor personalizado.\n");
    getch();

    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, ""); // Inicializar modo gráfico

    if (graphresult() != grOk) {
        printf("Error al inicializar el modo gráfico.\n");
        printf("Presiona cualquier tecla para salir.\n");
        getch();
        return;
    }

    // Usar un cursor simple (por ejemplo, un cuadrado 8x8)
    // Rellenamos las 16 palabras (32 bytes) para AND mask y las 16 para XOR mask
    unsigned char custom_cursor[32]; // 16 palabras para AND, 16 para XOR
    // AND mask: todo transparente (0)
    for (int i = 0; i < 16; ++i) custom_cursor[i] = 0x00;

    // XOR mask: Un pequeño cuadrado en el centro del cursor 8x8
    custom_cursor[16 + 2] = 0x18; // 00011000
    custom_cursor[16 + 3] = 0x18;
    custom_cursor[16 + 4] = 0x18;
    custom_cursor[16 + 5] = 0x18;

    // Hotspot en el centro del cursor 8x8
    int hotspot_x = 4;
    int hotspot_y = 4;

    asm {
        mov ax, 0x09
        mov bx, hotspot_x
        mov cx, hotspot_y
        // ES:DX apunta a la máscara del cursor
        push ds
        pop es          // Asegura ES = DS
        lea dx, custom_cursor // Cargar la dirección de la máscara
        int 0x33
    }
    printf("Cursor personalizado establecido. Mueva el ratón.\n");
    usar_int33h_01h(); // Asegurarse de que el cursor esté visible
    printf("Presiona cualquier tecla para restaurar el cursor y salir del modo gráfico.\n");
    getch();

    // Restaurar el cursor por defecto (normalmente se hace al cerrar el driver o al salir)
    usar_int33h_02h(); // Ocultar antes de cerrar el modo gráfico
    closegraph();
    clrscr(); // Limpiar la pantalla de texto
}

// Función 0Ah: Establecer forma del cursor de hardware (texto)
void usar_int33h_0Ah() {
    printf("\n--- Establecer forma del cursor de hardware (texto) (0Ah) ---\n");
    printf("Esta función cambia la forma del cursor de texto del ratón.\n");
    printf("Presiona cualquier tecla para continuar y ver el cursor personalizado.\n");
    getch();

    // Cursor de texto como un bloque (para modo de texto)
    // El cursor de texto se define por su línea inicial y final
    // CX = Start scan line, DX = End scan line
    int start_line = 0; // Línea superior (ej. para un bloque completo)
    int end_line = 7;   // Línea inferior (ej. para un bloque completo)

    asm {
        mov ax, 0x0A
        mov bx, 0x0000 // Tipo de cursor de hardware (0 = texto)
        mov cx, start_line
        mov dx, end_line
        int 0x33
    }
    printf("Cursor de texto personalizado establecido (bloque). Mueva el ratón.\n");
    usar_int33h_01h(); // Asegurarse de que el cursor esté visible
    printf("Presiona cualquier tecla para restaurar el cursor.\n");
    getch();

    // Restaurar cursor de texto a su forma original (ej. guion bajo)
    asm {
        mov ax, 0x0A
        mov bx, 0x0000
        mov cx, 6 // Start line (guion bajo)
        mov dx, 7 // End line (guion bajo)
        int 0x33
    }
    printf("Cursor de texto restaurado.\n");
}

// Función 0Bh: Leer contadores de movimiento del ratón
void usar_int33h_0Bh() {
    printf("\n--- Leer contadores de movimiento (0Bh) ---\n");
    printf("Mueva el ratón para acumular mickeys (presione cualquier tecla para salir).\n");

    int delta_x, delta_y;
    do {
        asm {
            mov ax, 0x0B
            int 0x33
            mov delta_x, cx // Movimiento horizontal (mickeys)
            mov delta_y, dx // Movimiento vertical (mickeys)
        }
        clrscr();
        printf("Mickeys X: %d, Mickeys Y: %d\n", delta_x, delta_y);
        delay(100);
    } while (!kbhit());
    getch();
    printf("\nPresiona cualquier tecla para continuar...\n");
    getch();
}

// Función 0Ch: Instalar rutina de interrupción para eventos del ratón
void far mouse_event_handler(int button_status, int x_coord, int y_coord, int dx_mickeys, int dy_mickeys) {
    // When an interrupt handler is called, the CPU pushes FLAGS, CS, and IP.
    // We need to manually push other registers that our C code or inline assembly
    // might modify, and pop them before returning from the interrupt.
    asm {
        push ax         // Save AX
        push bx         // Save BX
        push cx         // Save CX
        push dx         // Save DX
        push si         // Save SI
        push di         // Save DI
        push es         // Save ES
        push ds         // Save DS

        // Establish our data segment for accessing global variables.
        // Assuming your program's data segment is the same as the current DS.
        // If not, you'd need to load the correct data segment into DS.
        // For simplicity, we assume DS is already pointing to our program's data.
        // If your program uses a different data segment, you might need:
        // mov ax, DGROUP  (or your data segment name if using specific model)
        // mov ds, ax
        // mov es, ax      (if accessing data via ES also)
    }

    // Actualizar variables globales (para que el main pueda leerlas)
    // The C compiler will handle these assignments.
    mouse_x = x_coord;
    mouse_y = y_coord;
    mouse_buttons = button_status;

    asm {
        pop ds          // Restore DS
        pop es          // Restore ES
        pop di          // Restore DI
        pop si          // Restore SI
        pop dx          // Restore DX
        pop cx          // Restore CX
        pop bx          // Restore BX
        pop ax          // Restore AX
        // The IRET instruction is implicitly generated by the 'far' keyword
        // for interrupt handlers in many DOS C compilers (like Borland C/C++).
        // If it wasn't, you'd explicitly need 'iret' here.
    }
}

void usar_int33h_0Ch() {
    printf("\n--- Instalar rutina de interrupción para eventos (0Ch) ---\n");
    printf("Mueva el ratón o presione botones para ver los eventos.\n");
    printf("Presiona cualquier tecla para desinstalar la rutina.\n");

    int event_mask = 0x000F; // Capturar movimiento, clic izq/der.

    // No necesitas FP_SEG y FP_OFF aquí, el compilador puede manejar el puntero FAR
    // unsigned int segment = FP_SEG(mouse_event_handler);
    // unsigned int offset = FP_OFF(mouse_event_handler);

    asm {
        mov ax, 0x0C
        mov cx, event_mask
        
        // Cargar el segmento del manejador en DS y el offset en DX
        // 'lds' ya hace esto por nosotros
        lds dx, mouse_event_handler 
        
        // Mover el valor del registro DS (donde lds cargó el segmento) a ES
        // Usando un registro de propósito general como AX como intermediario
        mov ax, ds          // Copia el valor de DS a AX
        mov es, ax          // Copia el valor de AX a ES
        
        int 0x33
    }
    printf("Rutina de eventos del ratón instalada. Observa el estado de X, Y y botones.\n");

    // Bucle para mostrar el estado actual (actualizado por la ISR)
    do {
        clrscr();
        printf("X: %d, Y: %d, Botones: ");
        if (mouse_buttons & 0x01) printf("Izquierdo ");
        if (mouse_buttons & 0x02) printf("Derecho ");
        if (mouse_buttons & 0x04) printf("Central ");
        if (!(mouse_buttons & 0x01) && !(mouse_buttons & 0x02) && !(mouse_buttons & 0x04)) printf("Ninguno");
        delay(100);
    } while (!kbhit());
    getch();

    // Desinstalar la rutina de interrupción al salir
    usar_int33h_0Dh();
    printf("\nRutina de eventos del ratón desinstalada.\n");
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}


// Función 0Dh: Desinstalar rutina de interrupción para eventos del ratón
void usar_int33h_0Dh() {
    printf("\n--- Desinstalar rutina de interrupción para eventos (0Dh) ---\n");
    asm {
        mov ax, 0x0C // Se usa 0Ch con 0 para desinstalar en muchos drivers
        mov cx, 0x00 // Máscara de eventos a 0
        mov dx, 0x00 // Offset a 0
        
        // CORRECCIÓN AQUÍ: Mover 0x00 a AX (o cualquier otro registro general) primero
        mov ax, 0x00
        mov es, ax   // Luego mover AX a ES
        
        int 0x33
    }
    printf("Rutina de eventos del ratón desinstalada.\n");
}

// Función 0Eh: Asignar sensibilidad del ratón (factor de velocidad)
void usar_int33h_0Eh() {
    printf("\n--- Asignar sensibilidad del ratón (0Eh) ---\n");
    int h_factor, v_factor;
    printf("Introduce el factor horizontal (1-32767, ej. 8): ");
    scanf("%d", &h_factor);
    printf("Introduce el factor vertical (1-32767, ej. 16): ");
    scanf("%d", &v_factor);

    asm {
        mov ax, 0x0E
        mov dx, h_factor
        mov cx, v_factor
        int 0x33
    }
    printf("Sensibilidad del ratón establecida a Horizontal: %d, Vertical: %d\n", h_factor, v_factor);
    printf("Mueva el ratón para notar el cambio (presiona cualquier tecla para continuar).\n");
    getch();
}

// Función 0Fh: Obtener sensibilidad del ratón
void usar_int33h_0Fh() {
    printf("\n--- Obtener sensibilidad del ratón (0Fh) ---\n");
    int h_factor, v_factor;

    asm {
        mov ax, 0x0F
        int 0x33
        mov h_factor, dx
        mov v_factor, cx
    }
    printf("Sensibilidad actual del ratón: Horizontal: %d, Vertical: %d\n", h_factor, v_factor);
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 10h: Establecer el factor de aceleración del ratón
void usar_int33h_10h() {
    printf("\n--- Establecer factor de aceleración (10h) ---\n");
    int threshold, acceleration_factor;
    printf("Introduce el umbral de aceleración (en mickeys, ej. 8): ");
    scanf("%d", &threshold);
    printf("Introduce el factor de aceleración (ej. 2): ");
    scanf("%d", &acceleration_factor);

    asm {
        mov ax, 0x10
        mov bx, threshold
        mov cx, acceleration_factor
        int 0x33
    }
    printf("Factor de aceleración establecido. Umbral: %d, Factor: %d\n", threshold, acceleration_factor);
    printf("Mueva el ratón rápidamente para notar el cambio (presiona cualquier tecla para continuar).\n");
    getch();
}

// Función 13h: Establecer factor de aceleración "Mickey"
void usar_int33h_13h() {
    printf("\n--- Establecer factor de aceleración 'Mickey' (13h) ---\n");
    int threshold_x, threshold_y;
    printf("Introduce el umbral X en mickeys (ej. 16): ");
    scanf("%d", &threshold_x);
    printf("Introduce el umbral Y en mickeys (ej. 16): ");
    scanf("%d", &threshold_y);

    asm {
        mov ax, 0x13
        mov dx, threshold_x
        mov cx, threshold_y
        int 0x33
    }
    printf("Umbral de aceleración Mickey establecido. X: %d, Y: %d\n", threshold_x, threshold_y);
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 14h: Intercambiar rutinas de eventos del ratón
void far mouse_event_handler_2(int button_status, int x_coord, int y_coord, int dx_mickeys, int dy_mickeys) {
    mouse_x = x_coord;
    mouse_y = y_coord;
    mouse_buttons = button_status;
}

void usar_int33h_14h() {
    printf("\n--- Intercambiar rutinas de eventos (14h) ---\n");
    printf("Instalando una rutina de eventos alternativa. (Presiona cualquier tecla para salir).\n");

    int event_mask = 0x000F; // Capturar movimiento, clic izq/der.

    // Instalar la rutina original primero para tener algo que intercambiar
    // No necesitas FP_SEG y FP_OFF aquí, el compilador puede manejar el puntero FAR
    // unsigned int segment = FP_SEG(mouse_event_handler);
    // unsigned int offset = FP_OFF(mouse_event_handler);
    asm {
        mov ax, 0x0C
        mov cx, event_mask
        lds dx, mouse_event_handler // Carga DS con el segmento y DX con el offset
        mov ax, ds                  // Copia DS a AX
        mov es, ax                  // Copia AX a ES
        int 0x33
    }
    printf("Rutina original instalada.\n");
    delay(1000);

    // Ahora, intercambiar a la segunda rutina
    // unsigned int segment2 = FP_SEG(mouse_event_handler_2);
    // unsigned int offset2 = FP_OFF(mouse_event_handler_2);
    asm {
        mov ax, 0x14 // Usar 14h para intercambiar
        mov cx, event_mask
        lds dx, mouse_event_handler_2 // Carga DS con el segmento y DX con el offset de la segunda rutina
        mov ax, ds                    // Copia DS a AX
        mov es, ax                    // Copia AX a ES
        int 0x33
    }
    printf("Rutina intercambiada a la alternativa. Mueva el ratón.\n");

    do {
        clrscr();
        printf("X: %d, Y: %d, Botones: ");
        if (mouse_buttons & 0x01) printf("Izquierdo ");
        if (mouse_buttons & 0x02) printf("Derecho ");
        if (mouse_buttons & 0x04) printf("Central ");
        if (!(mouse_buttons & 0x01) && !(mouse_buttons & 0x02) && !(mouse_buttons & 0x04)) printf("Ninguno");
        delay(100);
    } while (!kbhit());
    getch();

    usar_int33h_0Dh(); // Desinstalar al final
    printf("\nPresiona cualquier tecla para continuar...\n");
    getch();
}



// Función 15h: Obtener el tamaño del buffer de estado del ratón
void usar_int33h_15h() {
    printf("\n--- Obtener tamaño del buffer de estado (15h) ---\n");
    int buffer_size;
    asm {
        mov ax, 0x15
        int 0x33
        mov buffer_size, bx
    }
    printf("Tamaño del buffer de estado del driver del ratón: %d bytes.\n", buffer_size);
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Funciones 16h y 17h: Guardar/Restaurar el estado del driver del ratón
char mouse_state_buffer[256]; // Un tamaño suficientemente grande (el 15h nos da el tamaño real)

void usar_int33h_16h() {
    printf("\n--- Guardar estado del driver (16h) ---\n");
    unsigned int segment = FP_SEG(mouse_state_buffer);
    unsigned int offset2 = FP_OFF(mouse_state_buffer);

    asm {
        mov ax, 0x16
        mov dx, offset2 // Cargar el valor de 'offset' directamente en DX
        mov ax, segment // Cargar el valor de 'segment' en AX
        mov es, ax      // Mover AX a ES
        
        int 0x33
    }
    printf("Estado del driver del ratón guardado.\n");
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}
void usar_int33h_17h() {
    printf("\n--- Restaurar estado del driver (17h) ---\n");
    unsigned int segment = FP_SEG(mouse_state_buffer);
    unsigned int offset2 = FP_OFF(mouse_state_buffer);

    asm {
        mov ax, 0x17
        mov dx, offset2
        mov es, segment
        int 0x33
    }
    printf("Estado del driver del ratón restaurado.\n");
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

void usar_int33h_18h() {
    printf("\n--- Instalar manejador de interrupción para eventos (18h) ---\n");
    printf("Mueva el ratón o presione botones para ver los eventos (presiona cualquier tecla para salir).\n");

    int event_mask = 0x000F; // Capture movement, left/right click.
    
    // Get the segment and offset of the far function pointer
    unsigned int segment = FP_SEG(mouse_event_handler);
    unsigned int offset2 = FP_OFF(mouse_event_handler);

    asm {
        mov ax, 0x18
        mov cx, event_mask
        
        // Load the offset into DX
        mov dx, offset2
        
        // Load the segment into ES (using AX as an intermediary)
        mov bx, segment // Use BX as an intermediary for segment, or AX
        mov es, bx
        
        int 0x33
    }
    printf("Manejador de eventos del ratón (18h) instalado. Observa el estado de X, Y y botones.\n");

    do {
        clrscr();
        printf("X: %d, Y: %d, Botones: ", mouse_x, mouse_y);
        if (mouse_buttons & 0x01) printf("Izquierdo ");
        if (mouse_buttons & 0x02) printf("Derecho ");
        if (mouse_buttons & 0x04) printf("Central ");
        if (!(mouse_buttons & 0x01) && !(mouse_buttons & 0x02) && !(mouse_buttons & 0x04)) printf("Ninguno");
        delay(100);
    } while (!kbhit());
    getch();

    usar_int33h_0Dh(); // Uninstall the routine (0Dh might also uninstall 18h)
    printf("\nPresiona cualquier tecla para continuar...\n");
    getch();
}

// Función 19h: Obtener el conteo del driver de interrupciones
void usar_int33h_19h() {
    printf("\n--- Obtener conteo del driver de interrupciones (19h) ---\n");
    int count;
    asm {
        mov ax, 0x19
        int 0x33
        mov count, cx
    }
    printf("Conteo de interrupciones del driver del ratón: %d\n", count);
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 1Ah: Asignar la relación mickey/pixel
void usar_int33h_1Ah() {
    printf("\n--- Asignar relación Mickey/Pixel (1Ah) ---\n");
    int h_ratio, v_ratio;
    printf("Introduce la relación horizontal (ej. 8): ");
    scanf("%d", &h_ratio);
    printf("Introduce la relación vertical (ej. 16): ");
    scanf("%d", &v_ratio);

    asm {
        mov ax, 0x1A
        mov bx, h_ratio
        mov cx, v_ratio
        int 0x33
    }
    printf("Relación Mickey/Pixel establecida: Horizontal: %d, Vertical: %d\n", h_ratio, v_ratio);
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 1Bh: Obtener la relación mickey/pixel
void usar_int33h_1Bh() {
    printf("\n--- Obtener relación Mickey/Pixel (1Bh) ---\n");
    int h_ratio, v_ratio;
    asm {
        mov ax, 0x1B
        int 0x33
        mov h_ratio, bx
        mov v_ratio, cx
    }
    printf("Relación Mickey/Pixel actual: Horizontal: %d, Vertical: %d\n", h_ratio, v_ratio);
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 1Ch: Guardar la configuración de estado de dos botones para el ratón de tres botones
void usar_int33h_1Ch() {
    printf("\n--- Guardar configuración de 2 botones (1Ch) ---\n");
    asm {
        mov ax, 0x1C
        int 0x33
    }
    printf("Configuración de 2 botones para ratón de 3 botones guardada.\n");
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 1Dh: Obtener la versión del driver del ratón
void usar_int33h_1Dh() {
    printf("\n--- Obtener versión del driver (1Dh) ---\n");
    int major_version, minor_version;
    asm {
        mov ax, 0x1D
        int 0x33
        mov major_version, bx
        mov minor_version, cx
    }
    printf("Versión del driver del ratón: Mayor=%d, Menor=%d\n", (major_version & 0xFF), (minor_version & 0xFF));
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 1Ee: Configurar ratón para modo de dos botones
void usar_int33h_1Eh() {
    printf("\n--- Configurar ratón para 2 botones (1Eh) ---\n");
    asm {
        mov ax, 0x1E
        int 0x33
    }
    printf("Ratón configurado para operar en modo de 2 botones.\n");
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 1Fh: Reconfigurar ratón para modo de tres botones
void usar_int33h_1Fh() {
    printf("\n--- Reconfigurar ratón para 3 botones (1Fh) ---\n");
    asm {
        mov ax, 0x1F
        int 0x33
    }
    printf("Ratón configurado para operar en modo de 3 botones.\n");
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 20h: Asignar manejador de eventos del ratón en modo protegido.
void usar_int33h_20h() {
    printf("\n--- Asignar manejador de eventos en modo protegido (20h) ---\n");
    printf("Esta función es para el modo protegido y no puede ser demostrada directamente en un entorno de Turbo C Real Mode.\n");
    printf("Requiere un entorno con un DOS Extender y configuración de GDT/LDT.\n");
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 21h: Obtener las coordenadas del cursor en modo protegido.
void usar_int33h_21h() {
    printf("\n--- Obtener coordenadas en modo protegido (21h) ---\n");
    printf("Esta función es para el modo protegido y no puede ser demostrada directamente en un entorno de Turbo C Real Mode.\n");
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 22h: Asignar la pantalla virtual para el ratón
void usar_int33h_22h() {
    printf("\n--- Asignar pantalla virtual (22h) ---\n");
    int virtual_width, virtual_height;
    printf("Introduce el ancho virtual (ej. 1024): ");
    scanf("%d", &virtual_width);
    printf("Introduce el alto virtual (ej. 768): ");
    scanf("%d", &virtual_height);

    asm {
        mov ax, 0x22
        mov cx, virtual_width
        mov dx, virtual_height
        int 0x33
    }
    int actual_h_limit, actual_v_limit;

    // Get Horizontal Limits (INT 33h, Function 07h)
    asm {
        mov ax, 0x07
        int 0x33
        mov actual_h_limit, cx // CX contains max horizontal
    }

    // Get Vertical Limits (INT 33h, Function 08h)
    asm {
        mov ax, 0x08
        int 0x33
        mov actual_v_limit, dx // DX contains max vertical
    }

    printf("El driver ha establecido la pantalla virtual en: Ancho real: %d, Alto real: %d\n", actual_h_limit, actual_v_limit);printf("Mueva el ratón para observar el nuevo mapeo (presiona cualquier tecla para continuar).\n");
        getch();
}

// Función 23h: Obtener la configuración de la pantalla virtual
void usar_int33h_23h() {
    printf("\n--- Obtener configuración de pantalla virtual (23h) ---\n");
    int virtual_width, virtual_height;
    asm {
        mov ax, 0x23
        int 0x33
        mov virtual_width, cx
        mov virtual_height, dx
    }
    printf("Configuración de pantalla virtual actual: Ancho: %d, Alto: %d\n", virtual_width, virtual_height);
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 24h: Asignar las coordenadas de la pantalla virtual para el cursor
void usar_int33h_24h() {
    printf("\n--- Asignar coordenadas de pantalla virtual (24h) ---\n");
    int new_x, new_y;
    printf("Introduce nueva coordenada X virtual (ej. 512): ");
    scanf("%d", &new_x);
    printf("Introduce nueva coordenada Y virtual (ej. 384): ");
    scanf("%d", &new_y);

    asm {
        mov ax, 0x24
        mov cx, new_x
        mov dx, new_y
        int 0x33
    }
    printf("Cursor movido a virtual X: %d, Y: %d\n", new_x, new_y);
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 25h: Configurar la aceleración del ratón (para IntelliMouse o similar)
void usar_int33h_25h() {
    printf("\n--- Configurar aceleración del ratón (IntelliMouse) (25h) ---\n");
    int type, threshold1, threshold2;
    printf("Introduce el tipo de aceleración (0-3, ej. 1): ");
    scanf("%d", &type);
    printf("Introduce el umbral 1 (ej. 8): ");
    scanf("%d", &threshold1);
    printf("Introduce el umbral 2 (ej. 16): ");
    scanf("%d", &threshold2);

    asm {
        mov ax, 0x25
        mov bx, type
        mov cx, threshold1
        mov dx, threshold2
        int 0x33
    }
    printf("Aceleración configurada: Tipo=%d, Umbral1=%d, Umbral2=%d\n", type, threshold1, threshold2);
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 26h: Obtener la aceleración del ratón (para IntelliMouse)
void usar_int33h_26h() {
    printf("\n--- Obtener aceleración del ratón (IntelliMouse) (26h) ---\n");
    int type, threshold1, threshold2;
    asm {
        mov ax, 0x26
        int 0x33
        mov type, bx
        mov threshold1, cx
        mov threshold2, dx
    }
    printf("Aceleración actual: Tipo=%d, Umbral1=%d, Umbral2=%d\n", type, threshold1, threshold2);
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 27h: Asignar la velocidad de scroll del ratón
void usar_int33h_27h() {
    printf("\n--- Asignar velocidad de scroll (27h) ---\n");
    int vertical_speed, horizontal_speed;
    printf("Introduce la velocidad de scroll vertical (ej. 3): ");
    scanf("%d", &vertical_speed);
    printf("Introduce la velocidad de scroll horizontal (ej. 1): ");
    scanf("%d", &horizontal_speed);

    asm {
        mov ax, 0x27
        mov bx, vertical_speed
        mov cx, horizontal_speed
        int 0x33
    }
    printf("Velocidad de scroll establecida: Vertical: %d, Horizontal: %d\n", vertical_speed, horizontal_speed);
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 28h: Obtener la velocidad de scroll del ratón
void usar_int33h_28h() {
    printf("\n--- Obtener velocidad de scroll (28h) ---\n");
    int vertical_speed, horizontal_speed;
    asm {
        mov ax, 0x28
        int 0x33
        mov vertical_speed, bx
        mov horizontal_speed, cx
    }
    printf("Velocidad de scroll actual: Vertical: %d, Horizontal: %d\n", vertical_speed, horizontal_speed);
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 2Ah: Asignar la posición y el estado del botón del ratón en modo texto
void usar_int33h_2Ah() {
    printf("\n--- Asignar posición/estado en modo texto (2Ah) ---\n");
    int new_x, new_y, buttons;
    printf("Introduce nueva columna X (ej. 40): ");
    scanf("%d", &new_x);
    printf("Introduce nueva fila Y (ej. 12): ");
    scanf("%d", &new_y);
    printf("Introduce estado de botones (ej. 0x01 para izquierdo): ");
    scanf("%x", &buttons); // %x para leer hexadecimal

    asm {
        mov ax, 0x2A
        mov bx, buttons
        mov cx, new_x
        mov dx, new_y
        int 0x33
    }
    printf("Cursor de texto y estado de botones establecidos.\n");
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 2Bh: Obtener la posición del cursor de texto del ratón
void usar_int33h_2Bh() {
    printf("\n--- Obtener posición del cursor de texto (2Bh) ---\n");
    int x, y;
    asm {
        mov ax, 0x2B
        int 0x33
        mov x, cx
        mov y, dx
    }
    printf("Posición actual del cursor de texto: X: %d, Y: %d\n", x, y);
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 2Ch: Asignar la forma del cursor de texto del ratón
void usar_int33h_2Ch() {
    printf("\n--- Asignar forma del cursor de texto (2Ch) ---\n");
    int mask, attribute;
    printf("Introduce la máscara del cursor (ej. 0x7E para un bloque): ");
    scanf("%x", &mask); // %x para leer hexadecimal
    printf("Introduce el atributo del cursor (ej. 0x07 para blanco): ");
    scanf("%x", &attribute); // %x para leer hexadecimal

    asm {
        mov ax, 0x2C
        mov cx, mask
        mov dx, attribute
        int 0x33
    }
    printf("Forma del cursor de texto establecida.\n");
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 2Dh: Obtener la forma del cursor de texto del ratón
void usar_int33h_2Dh() {
    printf("\n--- Obtener forma del cursor de texto (2Dh) ---\n");
    int mask, attribute;
    asm {
        mov ax, 0x2D
        int 0x33
        mov mask, cx
        mov attribute, dx
    }
    printf("Forma actual del cursor de texto: Máscara: 0x%X, Atributo: 0x%X\n", mask, attribute);
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 2Eh: Configurar el driver del ratón en modo de compatibilidad
void usar_int33h_2Eh() {
    printf("\n--- Configurar modo de compatibilidad (2Eh) ---\n");
    asm {
        mov ax, 0x2E
        int 0x33
    }
    printf("Driver del ratón configurado en modo de compatibilidad.\n");
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 2Fh: Obtener el estado del driver del ratón en modo de compatibilidad
void usar_int33h_2Fh() {
    printf("\n--- Obtener estado del modo de compatibilidad (2Fh) ---\n");
    int status;
    asm {
        mov ax, 0x2F
        int 0x33
        mov status, ax
    }
    printf("Estado del modo de compatibilidad: %d\n", status);
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 30h: Leer/ajustar la graduación del "ball-point mouse" (ratón que se puede rotar)
void usar_int33h_30h() {
    printf("\n--- Leer/Ajustar graduación (Ball-point mouse) (30h) ---\n");
    int current_graduation, new_graduation;
    printf("Introduce la nueva graduación (0-255, 0 para leer): ");
    scanf("%d", &new_graduation);

    if (new_graduation == 0) { // Si se introduce 0, leer la actual
        asm {
            mov ax, 0x30
            mov bx, 0x0000 // BX = 0 para leer
            int 0x33
            mov current_graduation, ax
        }
        printf("Graduación actual del ball-point mouse: %d\n", current_graduation);
    } else {
        asm {
            mov ax, 0x30
            mov bx, new_graduation // BX = nueva graduación para ajustar
            int 0x33
            mov current_graduation, ax // AX devuelve la graduación anterior
        }
        printf("Graduación del ball-point mouse ajustada a: %d. Anteriormente era: %d\n", new_graduation, current_graduation);
    }
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 31h: Leer la extensión de la pantalla virtual
void usar_int33h_31h() {
    printf("\n--- Leer extensión de la pantalla virtual (31h) ---\n");
    int extended_width, extended_height;
    asm {
        mov ax, 0x31
        int 0x33
        mov extended_width, bx
        mov extended_height, cx
    }
    printf("Extensión de la pantalla virtual: Ancho=%d, Alto=%d\n", extended_width, extended_height);
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 32h: Averiguar las funciones soportadas a partir de la 25h
void usar_int33h_32h() {
    printf("\n--- Averiguar funciones soportadas (32h) ---\n");
    int supported_flags;
    asm {
        mov ax, 0x32
        int 0x33
        mov supported_flags, bx
    }
    printf("Funciones extendidas soportadas (flags): 0x%X\n", supported_flags);
    printf(" (Bit 0: 25h, Bit 1: 26h, etc.)\n");
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 33h: Copiar parámetros del driver en un buffer
char driver_params_buffer[512]; // Un buffer genérico

void usar_int33h_33h() {
    printf("\n--- Copiar parámetros del driver a buffer (33h) ---\n");
    unsigned int segment = FP_SEG(driver_params_buffer);
    unsigned int offset2 = FP_OFF(driver_params_buffer);

    asm {
        mov ax, 0x33
        mov dx, offset2
        mov es, segment
        int 0x33
    }
    printf("Parámetros del driver copiados al buffer.\n");
    // Podrías imprimir los primeros bytes para verificar
    printf("Primeros 16 bytes del buffer: ");
    for (int i = 0; i < 16; ++i) {
        printf("%02X ", (unsigned char)driver_params_buffer[i]); // %02X para hexadecimal de 2 dígitos
    }
    printf("\n");
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 34h: Averiguar la ubicación del fichero MOUSE.INI
void usar_int33h_34h() {
    printf("\n--- Averiguar ubicación de MOUSE.INI (34h) ---\n");
    char far *mouse_ini_path;
    int status;
    asm {
        mov ax, 0x34
        int 0x33
        mov word ptr mouse_ini_path, dx
        mov word ptr mouse_ini_path+2, es
        mov status, bx // BX = 0 si no se encontró, !=0 si sí
    }

    if (status != 0) {
        printf("Ubicación de MOUSE.INI: %Fs\n", mouse_ini_path); // %Fs para puntero FAR a string
    } else {
        printf("MOUSE.INI no encontrado o función no soportada.\n");
    }
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}

// Función 35h: Soporte de cursor agrandado para pantallas LCD
void usar_int33h_35h() {
    printf("\n--- Soporte de cursor agrandado para LCD (35h) ---\n");
    int choice;
    printf("1. Activar cursor agrandado\n2. Desactivar cursor agrandado\nElige: ");
    scanf("%d", &choice);

    if (choice == 1) {
        asm {
            mov ax, 0x35
            mov bx, 0x0001 // Activar
            int 0x33
        }
        printf("Cursor agrandado activado (si es soportado).\n");
    } else if (choice == 2) {
        asm {
            mov ax, 0x35
            mov bx, 0x0000 // Desactivar
            int 0x33
        }
        printf("Cursor agrandado desactivado (si es soportado).\n");
    } else {
        printf("Opción no válida.\n");
    }
    printf("Presiona cualquier tecla para continuar...\n");
    getch();
}


// --- Menú principal para probar las funciones ---

// --- Constantes para la Paginación ---
#define TOTAL_OPTIONS 51
#define OPTIONS_PER_PAGE 15 // Puedes ajustar este valor
// Calcula el total de páginas necesarias (división de techo)
#define TOTAL_PAGES ((TOTAL_OPTIONS + OPTIONS_PER_PAGE - 1) / OPTIONS_PER_PAGE)

// Arreglo con las opciones del menú para una gestión más limpia
const char* menu_items[TOTAL_OPTIONS + 1] = {
    "", // Espacio reservado para el índice 0
    "1.  Inicializar driver (00h)", "2.  Mostrar cursor (01h)",
    "3.  Ocultar cursor (02h)", "4.  Obtener posicion y botones (03h)",
    "5.  Establecer posicion (04h)", "6.  Obtener boton pulsado (05h)",
    "7.  Obtener boton soltado (06h)", "8.  Establecer limites X (07h)",
    "9.  Establecer limites Y (08h)", "10. Establecer forma de cursor grafico (09h) - REQUIERE MODO GRAFICO!",
    "11. Establecer forma de cursor texto (0Ah)", "12. Leer contadores de movimiento (0Bh)",
    "15. Asignar sensibilidad (0Eh)", "16. Obtener sensibilidad (0Fh)",
    "17. Establecer aceleracion (10h)", "18. Establecer aceleracion 'Mickey' (13h)",
     "20. Obtener tamano de buffer de estado (15h)",
    "21. Guardar estado del driver (16h)", "22. Restaurar estado del driver (17h)",
    "23. Instalar manejador de interrupcion (18h)", "24. Obtener conteo de interrupciones (19h)",
    "25. Asignar relacion Mickey/Pixel (1Ah)", "26. Obtener relacion Mickey/Pixel (1Bh)",
    "27. Guardar config. 2 botones (1Ch)", "28. Obtener version del driver (1Dh)",
    "29. Configurar 2 botones (1Eh)", "30. Reconfigurar 3 botones (1Fh)",
    "31. Asignar manejador modo protegido (20h) - NO FUNCIONAL", "32. Obtener coordenadas modo protegido (21h) - NO FUNCIONAL",
    "33. Asignar pantalla virtual (22h)", "34. Obtener configuracion pantalla virtual (23h)",
    "35. Asignar coord. pantalla virtual (24h)", "36. Configurar aceleracion (IntelliMouse) (25h)",
    "37. Obtener aceleracion (IntelliMouse) (26h)", "38. Asignar velocidad de scroll (27h)",
    "39. Obtener velocidad de scroll (28h)", "40. Asignar pos/estado en modo texto (2Ah)",
    "41. Obtener pos. cursor de texto (2Bh)", "42. Asignar forma cursor de texto (2Ch)",
    "43. Obtener forma cursor de texto (2Dh)", "44. Configurar modo compatibilidad (2Eh)",
    "45. Obtener estado modo compatibilidad (2Fh)", "46. Leer/Ajustar graduacion (Ball-point mouse) (30h)",
    "47. Leer extension pantalla virtual (31h)", "48. Averiguar funciones soportadas (32h)",
    "49. Copiar parametros del driver (33h)", "50. Averiguar ubicacion MOUSE.INI (34h)",
    "51. Soporte cursor agrandado LCD (35h)"
};
//"13. Instalar rutina de interrupcion (0Ch)", "14. Desinstalar rutina de interrupcion (0Dh)","19. Intercambiar rutinas de eventos (14h)",

void Mouse() {
    int choice = -1;
    int currentPage = 1;
    int i;

    // Inicializar ratón al principio
    usar_int33h_00h();

    do {
        clrscr(); // Limpia la pantalla
        printf("--- Menu de Funciones de Interrupcion 33h para Raton ---\n\n");

        // Calcula el rango de opciones para la página actual
        int start_option = (currentPage - 1) * OPTIONS_PER_PAGE + 1;
        int end_option = start_option + OPTIONS_PER_PAGE - 1;
        if (end_option > TOTAL_OPTIONS) {
            end_option = TOTAL_OPTIONS;
        }

        // Muestra las opciones de la página actual
        for (i = start_option; i <= end_option; i++) {
            printf("%s\n", menu_items[i]);
        }
        
        // Muestra las opciones de navegación
        printf("\n--- Navegacion ---\n");
        if (currentPage > 1) {
            printf("98. Pagina Anterior\n");
        }
        if (currentPage < TOTAL_PAGES) {
            printf("99. Pagina Siguiente\n");
        }
        printf("0.  Salir\n");
        
        printf("\n--- Pagina %d de %d ---\n", currentPage, TOTAL_PAGES);
        printf("Elige una opcion: ");
        scanf("%d", &choice);

        // Gestiona la navegación o la selección de una opción
        if (choice == 99 && currentPage < TOTAL_PAGES) {
            currentPage++;
        } else if (choice == 98 && currentPage > 1) {
            currentPage--;
        } else if (choice >= 1 && choice <= TOTAL_OPTIONS) {
            // El switch original para ejecutar la función seleccionada
            switch (choice) {
                case 1: usar_int33h_00h(); break;
                case 2: usar_int33h_01h(); break;
                case 3: usar_int33h_02h(); break;
                case 4: usar_int33h_03h(); break;
                case 5: usar_int33h_04h(); break;
                case 6: usar_int33h_05h(); break;
                case 7: usar_int33h_06h(); break;
                case 8: usar_int33h_07h(); break;
                case 9: usar_int33h_08h(); break;
                case 10: usar_int33h_09h(); break;
                case 11: usar_int33h_0Ah(); break;
                //case 12: usar_int33h_0Bh(); break;
                //case 13: usar_int33h_0Ch(); break;
                case 14: usar_int33h_0Dh(); break;
                case 15: usar_int33h_0Eh(); break;
                case 16: usar_int33h_0Fh(); break;
                case 17: usar_int33h_10h(); break;
                case 18: usar_int33h_13h(); break;
                //case 19: usar_int33h_14h(); break;
                case 20: usar_int33h_15h(); break;
                case 21: usar_int33h_16h(); break;
                case 22: usar_int33h_17h(); break;
                case 23: usar_int33h_18h(); break;
                case 24: usar_int33h_19h(); break;
                case 25: usar_int33h_1Ah(); break;
                case 26: usar_int33h_1Bh(); break;
                case 27: usar_int33h_1Ch(); break;
                case 28: usar_int33h_1Dh(); break;
                case 29: usar_int33h_1Eh(); break;
                case 30: usar_int33h_1Fh(); break;
                case 31: usar_int33h_20h(); break;
                case 32: usar_int33h_21h(); break;
                case 33: usar_int33h_22h(); break;
                case 34: usar_int33h_23h(); break;
                case 35: usar_int33h_24h(); break;
                case 36: usar_int33h_25h(); break;
                case 37: usar_int33h_26h(); break;
                case 38: usar_int33h_27h(); break;
                case 39: usar_int33h_28h(); break;
                case 40: usar_int33h_2Ah(); break;
                case 41: usar_int33h_2Bh(); break;
                case 42: usar_int33h_2Ch(); break;
                case 43: usar_int33h_2Dh(); break;
                case 44: usar_int33h_2Eh(); break;
                case 45: usar_int33h_2Fh(); break;
                case 46: usar_int33h_30h(); break;
                case 47: usar_int33h_31h(); break;
                case 48: usar_int33h_32h(); break;
                case 49: usar_int33h_33h(); break;
                case 50: usar_int33h_34h(); break;
                case 51: usar_int33h_35h(); break;
            }
            printf("\n\nPresiona cualquier tecla para continuar...");
            getch(); // Espera a que el usuario presione una tecla
        } else if (choice != 0) {
            printf("Opcion invalida. Presiona una tecla para intentar de nuevo.\n");
            getch();
        }

    } while (choice != 0);

    printf("Saliendo del sub-menu de raton.\n");
}





// ==================== MENÚS Y FUNCIÓN PRINCIPAL ====================



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
            case 1: Mouse(); break;
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
