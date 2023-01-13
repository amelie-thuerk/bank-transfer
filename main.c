#include <stdio.h>
#include <string.h>

int main() {
    char repeat = 1;
    do {
        int input = 0;
        printf("Überweisungen\n1 - Suchen\n2 - Neu\n0 - Beenden\nEingabe: ");
        scanf("%d", &input);
        
        if (input > 2 || input < 0) {
            printf("Ungültige Eingabe. Bitte wiederholen.\n");
        }
        
        if (input == 0) {
            repeat = 0;
        }
        
        if (input == 1) {
            char search[128];
            printf("Kontonummer oder Name: ");
            scanf("%s", search);
            
            FILE* file = fopen("transfers.csv", "r");
            if (file == NULL) {
                return 1;
            }
        
            char line[1024];
            char row[6][128];
            
            while (fgets(line, sizeof(line), file)) {
                char* token = strtok(line, "\t");
                if (token != NULL) {
                    strcpy(row[0], token);
                    
                    for (int i = 1; i < 6 && token != NULL; i++) {
                        token = strtok(NULL, "\t");
                        strcpy(row[i], token);
                    }
                    
                    for (int i = 0; i < 4; i++) {
                        if (strcmp(row[i], search) == 0) {
                            printf("Von: %s (%s)\n", row[0], row[1]);
                            printf("An: %s (%s)\n", row[2], row[3]);
                            printf("Betrag: %s EUR für %s", row[4], row[5]);
                            break;
                        }
                    }
                }
                
            }
            
            if (fclose(file) != 0) {
                return 1;
            }
        }
        
        if (input == 2) {
            char source_name[128];
            printf("Quelle - Name: ");
            scanf("%s", source_name);
            
            char source_id[128];
            printf("Quelle - Kontonummer: ");
            scanf("%s", source_id);
            
            char target_name[128];
            printf("Ziel - Name: ");
            scanf("%s", target_name);
            
            char target_id[128];
            printf("Ziel - Kontonummer: ");
            scanf("%s", target_id);
            
            char amount[128];
            printf("Betrag: ");
            scanf("%s", amount);
            
            char purpose[128];
            printf("Verwendungszweck: ");
            scanf("%s", purpose);
            
            FILE* file = fopen("transfers.csv", "a");
            if (file == NULL) {
                return 1;
            }
            
            fprintf(file, "%s\t", source_name);
            fprintf(file, "%s\t", source_id);
            fprintf(file, "%s\t", target_name);
            fprintf(file, "%s\t", target_id);
            fprintf(file, "%s\t", amount);
            fprintf(file, "%s\n", purpose);
            
            if (fclose(file) != 0) {
                return 1;
            }
            
        }
        

    } while (repeat);
    
    return 0;
}

