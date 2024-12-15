#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Pustaka untuk menghitung waktu

// Fungsi untuk mencatat log laporan
void logReport(const char *message)
{
    FILE *logFile = fopen("log_report.txt", "a");
    if (logFile == NULL)
    {
        printf("Gagal mencatat log laporan.\n");
        return;
    }
    fprintf(logFile, "%s\n", message);
    fclose(logFile);
}

// Fungsi untuk membaca input dengan spasi
void readInput(char *buffer, int size)
{
    fgets(buffer, size, stdin);
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0'; // Hapus newline di akhir input
    }
}

// Fungsi untuk memastikan nama file memiliki ekstensi .txt
void ensureTxtExtension(char *filename)
{
    if (strstr(filename, ".txt") == NULL)
    {
        strcat(filename, ".txt");
    }
}

// Fungsi untuk membuat file
void createFile()
{
    char filename[100];
    printf("Masukkan nama file yang ingin dibuat: ");
    getchar(); // Membersihkan buffer input sebelumnya
    readInput(filename, sizeof(filename));
    ensureTxtExtension(filename);

    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Gagal membuat file.\n");
        logReport("Gagal membuat file.");
        return;
    }
    printf("File '%s' berhasil dibuat.\n", filename);
    logReport("File berhasil dibuat.");
    fclose(file);
}

// Fungsi untuk menulis ke file
void writeFile()
{
    char filename[100], content[500];
    printf("Masukkan nama file untuk menulis: ");
    getchar(); // Membersihkan buffer input sebelumnya
    readInput(filename, sizeof(filename));
    ensureTxtExtension(filename);

    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("File '%s' tidak ditemukan.\n", filename);
        logReport("Gagal menulis ke file (file tidak ditemukan).\n");
        return;
    }
    printf("Masukkan isi yang ingin ditulis (akhiri dengan ENTER):\n");
    readInput(content, sizeof(content));

    fprintf(file, "%s\n", content);
    printf("Berhasil menulis ke file '%s'.\n", filename);
    logReport("Berhasil menulis ke file.");
    fclose(file);
}

// Fungsi untuk membaca file
void readFile()
{
    char filename[100], content[500];
    printf("Masukkan nama file untuk dibaca: ");
    getchar(); // Membersihkan buffer input sebelumnya
    readInput(filename, sizeof(filename));
    ensureTxtExtension(filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File '%s' tidak ditemukan.\n", filename);
        logReport("Gagal membaca file (file tidak ditemukan).\n");
        return;
    }
    printf("Isi file '%s':\n", filename);
    while (fgets(content, sizeof(content), file))
    {
        printf("%s", content);
    }
    logReport("File berhasil dibaca.");
    fclose(file);
}

// Fungsi untuk menghapus file
void deleteFile()
{
    char filename[100];
    printf("Masukkan nama file untuk dihapus: ");
    getchar(); // Membersihkan buffer input sebelumnya
    readInput(filename, sizeof(filename));
    ensureTxtExtension(filename);

    if (remove(filename) == 0)
    {
        printf("File '%s' berhasil dihapus.\n", filename);
        logReport("File berhasil dihapus.");
    }
    else
    {
        printf("Gagal menghapus file '%s'.\n", filename);
        logReport("Gagal menghapus file (file tidak ditemukan).\n");
    }
}

int main()
{
    int choice;
    clock_t start, end; // Variabel untuk menghitung waktu eksekusi
    double exec_time;

    start = clock(); // Mulai hitung waktu eksekusi

    do
    {
        printf("\n=== Program File Manajemen Sederhana ===\n");
        printf("1. Buat File\n");
        printf("2. Tulis ke Dalam File\n");
        printf("3. Baca File\n");
        printf("4. Hapus File\n");
        printf("5. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createFile();
            break;
        case 2:
            writeFile();
            break;
        case 3:
            readFile();
            break;
        case 4:
            deleteFile();
            break;
        case 5:
            printf("Keluar dari program.\n");
            logReport("Program dihentikan.");
            break;
        default:
            printf("Pilihan tidak valid.\n");
            logReport("Pilihan tidak valid dipilih.");
        }
    } while (choice != 5);

    end = clock();                                      // Selesai hitung waktu eksekusi
    exec_time = (double)(end - start) / CLOCKS_PER_SEC; // Hitung durasi dalam detik

    // Menampilkan waktu eksekusi
    printf("Waktu eksekusi program: %.3f detik.\n", exec_time);

    // Mencatat waktu eksekusi ke log
    char logMessage[100];
    sprintf(logMessage, "Waktu eksekusi program: %.3f detik.", exec_time);
    logReport(logMessage);

    return 0;
}