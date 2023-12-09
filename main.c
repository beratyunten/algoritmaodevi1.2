#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sifrele(char *girdi, char *cikti) {
    FILE *girdiDosyasi, *ciktiDosyasi;
    char karakter;

    // Girdi dosyasini okuma modunda aciyor
    girdiDosyasi = fopen(girdi, "r");
    if (girdiDosyasi == NULL) {
        perror("Girdi dosyasini acma hatasi");
        exit(EXIT_FAILURE);
    }

    // Cikti dosyasini ise yazma moduna aciyor
    ciktiDosyasi = fopen(cikti, "w");
    if (ciktiDosyasi == NULL) {
        perror("Cikti dosyasini acma hatasi");
        fclose(girdiDosyasi);
        exit(EXIT_FAILURE);
    }

    // Girdi dosyasini sonuna kadar okuyacak
    while ((karakter = fgetc(girdiDosyasi)) != EOF) {
        // Kucuk harf ise sifreleyecek
        if ('a' <= karakter && karakter <= 'z') {
            karakter = 'a' + (karakter - 'a' + 3) % 26; // Sabit anahtar 3
            
			    // Sifreleme islemi yapilir: 'a' + (karakter - 'a' + 3) % 26 ile 3 basamak kaydirma yapilir.
			    // 'a' harfinin ASCII degeri 97'ye esit oldugu için, (karakter - 'a') ifadesi,
			    // aslinda karakterin alfabedeki konumunu temsil eder.
			    // Sonra 3 eklenir (sabit anahtarimiz), ve 26'ya mod alinir.
			    // Son olarak, 'a' eklenerek sifrelenmis harf elde edilir.
		    }
		        
		// Buyuk harf ise sifreleyecek
        else if ('A' <= karakter && karakter <= 'Z') {
            karakter = 'A' + (karakter - 'A' + 3) % 26; // Sabit anahtar 3
            
		        // Sifreleme islemi yapilir: (karakter - 'A' + 3) % 26 ile 3 basamak kaydirma yapilir.
		        // Kucuk harfi sifreleme isleminden tek farki 'A' nin ASCII degerinin 65 olmasi, islemler tamamen ayni.
        }
        
        // Sifrelenmis karakteri (texti) cikti dosyasina yaziyor
        fputc(karakter, ciktiDosyasi);
    }

    // Dosyalari kapatiyor
    fclose(girdiDosyasi);
    fclose(ciktiDosyasi);
}

void coz(char *girdi, char *cikti) {
    FILE *girdiDosyasi, *ciktiDosyasi;
    char karakter;

    // Girdi dosyasini okuma modunda aciyor
    girdiDosyasi = fopen(girdi, "r");
    if (girdiDosyasi == NULL) {
        perror("Girdi dosyasini acma hatasi");
        exit(EXIT_FAILURE);
    }

    // Cikti dosyasini ise yazma modunda aciyor
    ciktiDosyasi = fopen(cikti, "w");
    if (ciktiDosyasi == NULL) {
        perror("Cikti dosyasini acma hatasi");
        fclose(girdiDosyasi);
        exit(EXIT_FAILURE);
    }

    // Girdi dosyasini sonuna kadar okuyacak
    while ((karakter = fgetc(girdiDosyasi)) != EOF) {
        // Kucuk harf ise sifreyi cozecek
        if ('a' <= karakter && karakter <= 'z') {
            karakter = 'a' + (karakter - 'a' - 3 + 26) % 26; // Sabit anahtar 3
            
            	// Sifreleme islemi yapilir: 'a' + (karakter - 'a' - 3 + 26) % 26 ile 3 basamak geri kaydirma yapilir.
            	// Islemin 0 dan kucuk cikmamasi icin +26 ekledik geri kalan mantik benzer,
            	// a'nin ASCII degeri 97, karakterden a'yi cikarip - 3 daha yapiyoruz (3 basamak geri gidelim diye).
            	// Mod 26 alip sifreli harfi cozup sifrelenmemis haline dondurmus oluyoruz.
        }
        // Buyuk harf ise sifreyi cozecek
        else if ('A' <= karakter && karakter <= 'Z') {
            karakter = 'A' + (karakter - 'A' - 3 + 26) % 26; // Sabit anahtar 3
            
            	// Sifreleme islemi yapilir: 'A' + (karakter - 'a' - 3 + 26) % 26 ile 3 basamak geri kaydirma yapilir.
            	// kucuk harfi cozme ile ayni islemler A'nin ASCII degeri 65 tek fark bu.
        }
        // Çozulmus karakteri cikti dosyasina yazacak
        fputc(karakter, ciktiDosyasi);
    }

    // Dosyalari kapat
    fclose(girdiDosyasi);
    fclose(ciktiDosyasi);
}

int main() {
    int secim;
    char girdiDosyaAdi[100], ciktiDosyaAdi[100];
	
	// Kullaniciya arayuzu gosteriyor ve gerekli verileri aliyoruz
    printf("Metin Sifreleyici/Cozucu\n");
    printf("Bir secim yapin:\n");
    printf("1. Sifrele\n");
    printf("2. Coz\n");
    printf("Seciminiz: ");
    
    // Kullanicinin secimini aliyoruz
	if (scanf("%d", &secim) != 1 || (secim != 1 && secim != 2)) {
	        printf("Gecersiz secim. Lutfen sadece 1 veya 2 giriniz.\n");
	        exit(0);
	    }
	    
    // Girdi ve cikti dosya adlarini aldik
    printf("Girdi dosya adini girin: ");
    scanf("%s", girdiDosyaAdi);

    printf("Cikti dosya adini girin: ");
    scanf("%s", ciktiDosyaAdi);

    // Kullanicinin secimine gore islem sonucu
    switch (secim) {
        case 1:
            sifrele(girdiDosyaAdi, ciktiDosyaAdi);
            printf("Sifreleme tamamlandi.\n");
            break;
        case 2:
            coz(girdiDosyaAdi, ciktiDosyaAdi);
            printf("Cozme tamamlandi.\n");
            break;
        default:
            printf("Gecersiz secim.\n");
            break;
    }

    return 0;
}

