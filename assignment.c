#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct sled
{
    int x,
        y,
        orientation,
        totalDistance;
};

char map[30][30];
FILE *pMap;
FILE *cmds;
struct sled my_sled;
struct sled *p_sled = &my_sled;


void initialise_map(char map[30][30])
{
    for(int i = 0; i < 30; i++) {
        for(int j = 0; j < 30; j++) {
            map[i][j] = '.';
        }
    }    
}


void populate_map(FILE *pMap,char map[30][30])
{
    int posx;
    int posy;
    char symbol;

    char *sp;

    char line[15];
    pMap = fopen("map.txt", "r");
    while(fgets(line, 15, pMap) != NULL) {
        
        sp = strtok(line, ",");
        posx = atoi(sp);

        sp = strtok(NULL, ",");
        posy = atoi(sp);

        sp = strtok(NULL, "\n");
        symbol = *sp;

        map[posx][posy] = symbol;
    }

    fclose(pMap);
}


void print_map(char map[30][30])
{
    for(int i = 29; i >= 0; i--) {
        for(int j = 0; j < 30; j++) {
            printf("%C", map[i][j]);
        }printf("\n");
    }
}


int process_command(FILE *cmds, char map[30][30], struct sled *p_sled)
{   
    char command[20];
    int command_value;

    char line[100];
    char *sp;

    cmds = fopen("sledcommands.txt", "r");
    while(fgets(line, 100, cmds) != NULL) {

        sp = strtok(line, " ");
        strcpy(command, sp);

        sp = strtok(NULL, "\n");
        command_value = atoi(sp);

        if (strcmp(command, "FORWARD") == 0) {
            p_sled->totalDistance += command_value;
            if((my_sled.orientation/90) % 4 == 0)
                p_sled->y += command_value;
            else if((my_sled.orientation/90) % 4 == 1)
                p_sled->x += command_value;
            else if((my_sled.orientation/90) % 4 == 2)
                p_sled->y -= command_value;
            else if((my_sled.orientation/90) % 4 == 3)
                p_sled->x -= command_value;
        }
        
        if (strcmp(command, "BACK") == 0) {
            p_sled->totalDistance += command_value;
            if((my_sled.orientation/90) % 4 == 0)
                p_sled->y += command_value;
            else if((my_sled.orientation/90) % 4 == 1)
                p_sled->x += command_value;
            else if((my_sled.orientation/90) % 4 == 2)
                p_sled->y -= command_value;
            else if((my_sled.orientation/90) % 4 == 3)
                p_sled->x -= command_value;
        }

        if (strcmp(command, "TURN") == 0) {
            p_sled->orientation += command_value;
        }
    }
    return 0;
}


void print_sled(struct sled my_sled)
{
    printf("sled status:\n");
    printf("location %d,%d\n", my_sled.x, my_sled.y);
    printf("orientation %d degrees\n", my_sled.orientation);
    printf("distance travelled %d\n", my_sled.totalDistance);
    printf("end sled status.\n");
}


void print_symbol(char map[30][30], struct sled my_sled)
{
    printf("sled is flying over symbol %C\n", map[my_sled.x][my_sled.y]);
}

int process_command(FILE *cmds, char map[30][30], struct sled *p_sled)
{   
    int total_commands;

    char command[20];
    int command_value;

    char line[100];
    char *sp;

    while(fgets(line, 100, cmds) != NULL) {

        sp = strtok(line, " ");
        strcpy(command, sp);

        sp = strtok(NULL, "\n");
        command_value = atoi(sp);


        if (strcmp(command, "FORWARD") == 0) {
            p_sled->totalDistance += command_value;
            if((p_sled->orientation/90) % 4 == 0)
                p_sled->y += command_value;
                total_commands++;
            else if((p_sled->orientation/90) % 4 == 1)
                p_sled->x += command_value;
                total_commands++;
            else if((p_sled->orientation/90) % 4 == 2)
                p_sled->y -= command_value;
                total_commands++;
            else if((p_sled->orientation/90) % 4 == 3)
                p_sled->x -= command_value;
                total_commands++;
        }

        if (strcmp(command, "BACK") == 0) {
            p_sled->totalDistance += command_value;
            if((p_sled->orientation/90) % 4 == 0)
                p_sled->y -= command_value;
                total_commands++;
            else if((p_sled->orientation/90) % 4 == 1)
                p_sled->x -= command_value;
                total_commands++;
            else if((p_sled->orientation/90) % 4 == 2)
                p_sled->y += command_value;
                total_commands++;
            else if((p_sled->orientation/90) % 4 == 3)
                p_sled->x += command_value;
                total_commands++;
        }

        if (strcmp(command, "TURN") == 0) {
            p_sled->orientation += command_value;
            total_commands++;
            if(p_sled->orientation >= 360)
                p_sled->orientation -= 360;
        }
    }
    return 0;
}



int main()
{
    initialise_map(map);
    populate_map(pMap, map);
    print_map(map);

    process_command(cmds, map, p_sled);
    print_sled(my_sled);
    print_symbol(map, my_sled);
}