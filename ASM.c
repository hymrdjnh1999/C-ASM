#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct doiBong
{
    char teamID[20];
    char teamName[100];
    char coachName[100];
    int thang;
    int thua;
    int hoa;
    int tongTran;
    int tongdiem;
};

struct schedule
{
    char idTeam1[50];
    char idTeam2[50];
    char nameTeam1[20];
    char nameTeam2[20];
    char tranDau[50];
    char ngayDau[50];
    char gioDau[50];
    char sanDau[50];
    int pointTeam1;
    int pointTeam2;
};

int teamCount = 0;
int scheduleCount = 0;
struct doiBong *team = NULL;
struct schedule *schedule = NULL;

void mainMenu();
void menu1();
void editTeam();
void printListTeam();
int addTeam();
struct doiBong inputInforTeam();

void printSchedule();
int creatSchedule();
void menu2();
struct schedule inputInforSchedule();
void KQTD();
void thongKe();
void sapxepBXH();

char checkYN(char yn);                     //Ham check yes no
int checkInputSpecialCharacter(char *arr); // Hàm check nhập vào khoảng trắng và kí tự đặc biệt
int checkTeamID(char *arr);                // hàm check id trùng hay không
int checkCoachName(char *name);            // hàm check tên hlv
char *chuanHoaChuoi(char *arr);            // hàm Chuẩn hóa
int checkInput(int select);                // Hàm Check select của switch
int checkCompareID(char *arr);             // Hàm so sánh id
int compareidTran(char *arr);              // Hàm so sánh tên trận đấu
int checkCompareName(char *arr);           // Hàm so sánh tên đội
int compareTranDau(char *arr);
int ReadTeamsFromFile(char *fileName, int *pCount, struct doiBong *pListStudents);
int WriteTeamsToFile(struct doiBong *pListStudents, int count, char *fileName);
int ReadScheduleFromFile(char *fileName, int *pCount, struct schedule *pListStudents);
int WriteScheduleToFile(struct schedule *pListStudents, int count, char *fileName);
int main(int argc, char const *argv[])
{
    ReadTeamsFromFile("VL2018Teams.dat", &teamCount, team);
    fflush(stdin);
    if (team == NULL)
    {
        team = (struct doiBong *)malloc((teamCount + 1) * sizeof(struct doiBong));
    }
    mainMenu();
    return 0;
}

void mainMenu()
{
    int choose;
    while (1)
    {
        system("cls");
        printf("--- Chao mung den voi V-League 2018 ---\n");
        printf("\n===================================\n");
        printf("| 1. Quan Ly danh sach doi bong   |\n");
        printf("| 2. Quan ly lich thi dau         |\n");
        printf("| 3. Quan ly ket qua thi dau      |\n");
        printf("| 4. Thong ke                     |\n");
        printf("| 0. Thoat                        |\n");
        printf("===================================\n\n");
        printf("#Chon: ");
        choose = checkInput(choose);
        printf("\n==================================\n");
        switch (choose)
        {
        case 1:
            menu1();
            break;
        case 2:
            ReadTeamsFromFile("VL2018Teams.dat", &teamCount, team);
            menu2();
            break;
        case 3:
            ReadScheduleFromFile("VL2018Schedules.dat", &scheduleCount, schedule);
            ReadTeamsFromFile("VL2018Teams.dat", &teamCount, team);
            KQTD();
            break;
        case 4:
            // ReadTeamsFromFile("VL2018Teams.dat", &teamCount, team)
            ReadScheduleFromFile("VL2018Schedules.dat", &scheduleCount, schedule);
            ReadTeamsFromFile("VL2018Teams.dat", &teamCount, team);
            thongKe();
            break;
        case 0:
            free(team);
            free(schedule);
            printf("Chuc cac doi dat duoc ket qua tot trong mua V-League 2018!!!");
            exit(0);
            break;

        default:
            printf("Sai! An 1 phim bat ki de tiep tuc...");
            fflush(stdin);
            getchar();
            break;
        }
    }
}
void menu1()
{

    int select;
    while (1)
    {
        system("cls");
        printf("========================================\n");
        printf("| Quan ly danh sach doi bong           |\n");
        printf("========================================\n");
        printf("| 1. xem danh sach doi bong            |\n");
        printf("| 2. cap nhap thong tin  doi bong      |\n");
        printf("| 3. them moi mot doi bong             |\n");
        printf("| 0. tro ve menu chinh                 |\n");
        printf("========================================\n\n");
        printf("#chon : ");
        select = checkInput(select); //Check select
        switch (select)
        {
        case 1:
            printListTeam();
            printf("An 1 phim bat ki de tiep tuc...");
            fflush(stdin);
            getchar();
            break;
        case 2:
            editTeam();
            break;
        case 3:
            teamCount = addTeam();
            break;
        case 0:
            mainMenu();
            break;
        default:
            printf("\nSai!\nAn 1 phim bat ki de tiep tuc...");
            fflush(stdin);
            getchar();
            break;
        }
    }
}

int addTeam()
{
    ReadTeamsFromFile("VL2018Teams.dat", &teamCount, team);

    char yn;
    while (1) //Vòng chính tiếp tục chạy đến khi nào nhập vào != n | N
    {

        team = (struct doiBong *)realloc(team, (teamCount + 1) * sizeof(struct doiBong));
        system("cls");
        printf("Nhap thong tin doi thu %d\n", teamCount + 1);
        *(team + teamCount) = inputInforTeam(team, teamCount);
        teamCount++;
        printf("Ban co muon tiep tuc?(y/n):  ");
        yn = checkYN(yn);
        if (yn == 'n' || yn == 'N')
        { // vì nhập n||N nên thông báo đã bảo lưu giá trị nhập và trả về số tượng team.
            printf("Da Luu! An mot phim bat ki de quay lai...");
            fflush(stdin);
            WriteTeamsToFile(team, teamCount, "VL2018Teams.dat");
            fflush(stdin);
            getchar();

            return teamCount;
        }
    }
}

int checkCompareName(char *arr) // Hàm so sánh tên đội
{
    for (int i = 0; i < teamCount; i++)
    {
        if (strcmp(arr, (team + i)->teamName) == 0)
        {
            return 0;
        }
    }
    return 1;
}
char *chuanHoaChuoi(char *arr)
{

    for (int i = 0; i < strlen(arr); i++) //Vòng xóa kí tự trắng ở đầu và in hoa kí tự đầu
    {
        if (*(arr + 0) == ' ' || (*(arr + 0) >= 'a' && *(arr + 0) <= 'z'))
        {
            if (*(arr + 0) >= 'a' && *(arr + 0) <= 'z')
            {
                *(arr + 0) -= 32;
            }
            else
            {
                strcpy(arr + 0, arr + 1);
                i--;
            }
        }
        else
        {
            if (*(arr + i) == ' ' && *(arr + (i + 1)) == ' ') //xóa khoảng trắng
            {
                strcpy(arr + i, arr + (i + 1));
                i--;
            }
            else
            {
                if (*(arr + i) == ' ' && (*(arr + (i + 1)) >= 'a' && *(arr + (i + 1)) <= 'z'))
                {
                    *(arr + (i + 1)) -= 32;
                }
            }
        }
    }
    if (arr[strlen(arr) - 1] == ' ')
    {
        arr[strlen(arr) - 1] = '\0';
    }

    return arr;
}

int checkCoachName(char *name)
{
    for (int i = 0; i < strlen(name); i++)
    {
        if ((*(name + i) < 'a' && *(name + i) < 'z') || (*(name + i) < 'A') && *(name + i) > 'Z')
        {
            return 0;
        }
    }
    return 1;
}
int checkInputSpecialCharacter(char *arr) // hàm check nhập kí tự đặc biệt và enter
{
    int check = 0;
    if (arr[0] == '\n') // Nếu là dấu cách hoặc là enter thì hàm trả về false
    {
        return 0;
    }
    else //nếu không
    {

        for (int i = 0; i < strlen(arr); i++) // tìm trong chuỗi có kí tự đặc biệt nào không , nếu có sẽ return về 0 luôn
        {

            if ((arr[i] >= 'a' && arr[i] <= 'z') || (arr[i] >= 'A' && arr[i] <= 'Z') || (arr[i] >= '0' && arr[i] <= '9') || arr[i] == ' ')
            {
                check++;
            }
            else
            {
                return 0;
            }
        }
        if (check != 0)
        {
            return 1;
        }
    }
}

int checkCompareID(char *arr)
{

    for (int i = 0; i < teamCount; i++)
    {
        if (strcmp(arr, (team + i)->teamID) == 0)
        {
            return 1;
        }
    }

    return 0;
}
struct doiBong inputInforTeam() //Hàm nhập thông tin đội
{
    struct doiBong newTeam;
    printf("| Nhap ID : ");
    while (1)
    {
        int checkWhiteSpace = 0;
        fflush(stdin);
        scanf("%[^\n]s", newTeam.teamID);
        checkCompareID(newTeam.teamID);
        for (int i = 0; i < strlen(newTeam.teamID); i++)
        {
            if (newTeam.teamID[i] == ' ')
            {
                checkWhiteSpace++;
            }
        }
        int checkCMPID = checkInputSpecialCharacter(newTeam.teamID);
        if (checkCompareID(newTeam.teamID) == 0 && checkCMPID == 1 && checkWhiteSpace == 0)
        {
            break;
        }
        else
        {
            printf("Moi Nhap lai ID : ");
        }
    }

    printf("| Nhap ten doi : ");
    while (1)
    {
        fflush(stdin);
        scanf("%[^\n]s", newTeam.teamName);
        int checkTeamName = checkInputSpecialCharacter(newTeam.teamName);
        checkCompareName(newTeam.teamName);
        if (checkTeamName == 1 && checkCompareName(newTeam.teamName) == 1)
        {
            break;
        }
        else
        {
            printf("Ten doi da ton tai hoac co ki tu dac biet!!!!\n");
            printf("Nhap lai ten doi: ");
        }
    }
    printf("| Nhap ten HLV : ");
    while (1)
    {
        int checkCoachName = 0;
        fflush(stdin);
        scanf("%[^\n]s", newTeam.coachName);
        chuanHoaChuoi(newTeam.coachName); // Chuẩn hóa chuỗi
        for (int i = 0; i < strlen(newTeam.coachName); i++)
        {
            if (newTeam.coachName[0] == '\n')
            {
                checkCoachName++;
                break;
            }
            else if ((newTeam.coachName[i] >= 'a' && newTeam.coachName[i] <= 'z') || (newTeam.coachName[i] >= 'A' && newTeam.coachName[i] <= 'Z') || newTeam.coachName[i] == ' ')
            { // trong khoảng chữ cái
                checkCoachName = 0;
            }
            else
            {
                checkCoachName++;
                break;
            }
        }
        if (checkCoachName == 0)
        {
            break;
        }
        else
        {
            printf("Moi nhap lai ten HLV: ");
        }
    }
    newTeam.thang = 0;
    newTeam.thua = 0;
    newTeam.hoa = 0;
    newTeam.tongdiem = 0;
    newTeam.tongTran = 0;
    return newTeam;
}

void printListTeam()
{
    system("cls");
    fflush(stdin);
    ReadTeamsFromFile("VL2018Teams.dat", &teamCount, team);
    printf("--------------------------------------------------------------------------\n");
    printf("|                             Danh Sach Doi                              |\n");
    printf("--------------------------------------------------------------------------\n");
    printf("| %-6s | %-15s | %-20s | %-20s |\n", "STT", "ID doi", "Ten Doi", "Ten HLV");
    printf("--------------------------------------------------------------------------\n");
    for (int i = 0; i < teamCount; i++)
    {
        printf("| %-6d | %-15s | %-20s | %-20s |\n", i + 1, (team + i)->teamID, (team + i)->teamName, (team + i)->coachName);
    }
    printf("--------------------------------------------------------------------------\n");
}

void editTeam()
{
    ReadTeamsFromFile("VL2018Teams.dat", &teamCount, team);

    if (teamCount == 0)
    {
        system("cls");
        printf("Khong co gi!!! An 1 phim bat ki de quay lai...");
        fflush(stdin);
        getchar();
    }
    else
    {
        system("cls");
        char yn, ynMain;
        int checkHLV = 0;
        char teamName[100], coachName[100], id[100], teamID[100]; // Mảng lưu giá trị tạm thời
        int indexTeam = -1;
        while (1)
        {
            printListTeam(team, teamCount);

            printf("Moi nhap team id doi : ");
            while (1)
            {
                fflush(stdin);
                scanf("%[^\n]s", id);
                for (int i = 0; i < teamCount; i++)
                {
                    if (strcmp(id, (team + i)->teamID) == 0)
                    {
                        indexTeam = i;
                    }
                }
                int checkid1 = checkInputSpecialCharacter(id);
                if (checkid1 == 1 && indexTeam != -1)
                {
                    break;
                }
                else
                {
                    printf("Co ki tu dac biet hoac id khong ton tai ton tai!!!\nmoi nhap lai id doi : ");
                }
            }
            printf("Nhap ten doi : ");
            while (1)
            {
                int checkTeamName = -1;
                fflush(stdin);
                scanf("%[^\n]s", teamName);

                for (int i = 0; i < teamCount; i++)
                {
                    if ((strcmp(teamName, (team + i)->teamName) == 0) && i != indexTeam) // nếu tên đội tại các index khác tên đội tại indexTeam thì tăng biến chekc lên
                    {
                        checkTeamName = 1;
                    }
                }
                int check = checkInputSpecialCharacter(teamName);
                if (check == 1 && checkTeamName != 1)
                {
                    break;
                }
                else
                {
                    printf("Ten doi da ton tai hoac co ki tu dac biet!!!\nMoi nhap lai ten doi: ");
                }
            }

            printf("Nhap ten HLV : ");
            while (1)
            {

                fflush(stdin);
                scanf("%[^\n]s", coachName);
                chuanHoaChuoi(coachName); // Chuẩn hóa chuỗi
                for (int i = 0; i < strlen(coachName); i++)
                {
                    if (coachName[0] == '\n')
                    {
                        checkHLV++;
                        break;
                    }
                    else if ((coachName[i] >= 'a' && coachName[i] <= 'z') || (coachName[i] >= 'A' && coachName[i] <= 'Z') || coachName[i] == ' ')
                    { // trong khoảng chữ cái
                        checkHLV = 0;
                    }
                    else
                    {
                        checkHLV++;
                        break;
                    }
                }
                if (checkHLV == 0)
                {
                    break;
                }
                else
                {
                    printf("Moi nhap lai ten HLV: ");
                }
            }
            printf("Ban co muon cap nhat(y/n): ");
            yn = checkYN(yn);
            if (yn == 'y' || yn == 'Y') //Nếu muốn cập nhật thì copy giá trị vào mảng struct này :v.
            {
                strcpy((team + indexTeam)->teamName, teamName);
                strcpy((team + indexTeam)->coachName, coachName);
                printf("Thong tin da duoc cap nhat...\n");
                fflush(stdin);
                WriteTeamsToFile(team, teamCount, "VL2018Teams.dat");
                fflush(stdin);
            }
            printf("Ban co muon tiep tuc cap nhat(y/n): ");
            ynMain = checkYN(ynMain); // ynMain Có muốn cập nhật thêm đội nào không
            if (ynMain == 'N' || ynMain == 'n')
            {
                break;
            }
        }
    }
}

int checkInput(int select)
{
    while (1)
    {
        fflush(stdin);
        int check = scanf("%d", &select);
        if (check == 1 && select >= 0)
        {
            return select;
        }
        else
        {
            printf("Moi nhap lai : ");
        }
    }
}

char checkYN(char yn) //Hàm check nhập yes no
{
    while (1)
    {

        fflush(stdin);
        scanf("%c", &yn);
        if ((yn == 'y' || yn == 'Y') || (yn == 'n' || yn == 'N'))
        {
            return yn;
        }
        else
        {
            printf("Nhap sai! Nhap lai: ");
        }
    }
}

void menu2()
{
    ReadScheduleFromFile("VL2018Schedules.dat", &scheduleCount, schedule);
    if (schedule == NULL)
    {
        schedule = (struct schedule *)malloc((scheduleCount + 1) * sizeof(struct schedule));
    }
    int choose;

    while (1)
    {
        system("cls");
        printf("========================================\n");
        printf("| Quan ly lich thi dau                 |\n");
        printf("========================================\n");
        printf("| 1. xem lich thi dau                  |\n");
        printf("| 2. Tao lich thi dau                  |\n");
        printf("| 0. tro ve menu chinh                 |\n");
        printf("========================================\n\n");
        printf("#chon : ");
        choose = checkInput(choose);
        switch (choose)
        {
        case 1:
            printSchedule();
            printf("An 1 phim bat ki...");
            fflush(stdin);
            getchar();
            break;
        case 2:
            creatSchedule();
            break;
        case 0:
            mainMenu();
            break;
        default:
            printf("Nhap sai rui!!!\n\nNhap 1 phim bat ki de tiep tuc...");
            fflush(stdin);
            getchar();
            printf("\n");
            break;
        }
    }
}

int compareTranDau(char *arr)
{
    for (int i = 0; i < scheduleCount; i++)
    {
        if (strcmp(arr, (schedule + i)->tranDau) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int creatSchedule()
{
    // ReadTeamsFromFile("VL2018Teams.dat", &teamCount, team);
    char yn;
    if (teamCount < 2)
    {
        system("cls");
        printf("Lam gi co du doi ma TAO LICH !\nNhap 1 phim bat ki de tiep tuc...");
        fflush(stdin);
        getchar();
    }
    else
    {
        while (1)
        {
            system("cls");
            printListTeam(team, teamCount);
            schedule = (struct schedule *)realloc(schedule, (1 + scheduleCount) * sizeof(struct schedule));

            printf("---------- Tao Lich Thi Dau ----------\n");
            *(schedule + scheduleCount) = inputInforSchedule();
            scheduleCount++;
            printf("Ban co muon tiep tuc(y/n)? ");
            fflush(stdin);
            WriteScheduleToFile(schedule, scheduleCount, "VL2018Schedules.dat");
            yn = checkYN(yn);
            if (yn == 'n' || yn == 'N')
            {
                return scheduleCount;
            }
        }
    }
}

struct schedule inputInforSchedule() // Hàm nhập thông tin lịch thi đấu
{
    struct schedule newSchedule;
    int indexTeam1 = -1;
    int indexTeam2 = -1;
    char date[10];
    printf("| Tran Dau : ");
    while (1)
    {
        fflush(stdin);
        scanf("%[^\n]s", newSchedule.tranDau);
        // int check = checkInputSpecialCharacter(newSchedule.tranDau);
        int cmp = -1;
        for (int i = 0; i < scheduleCount; i++)
        {
            if (strcmp(newSchedule.tranDau, (schedule + i)->tranDau) == 0)
            {
                cmp = i;
            }
        }
        if (cmp == -1)
        {
            break;
        }
        else
        {
            printf("Trung tran dau hoac co ki tu dac biet!!!\nMoi nhap lai tran dau : ");
        }
    }
    printf("| ten doi thu 1 : ");
    while (1)
    {
        fflush(stdin);
        scanf("%[^\n]s", newSchedule.nameTeam1);

        for (int i = 0; i < teamCount; i++)
        {
            if (strcmp(newSchedule.nameTeam1, (team + i)->teamName) == 0)
            {
                indexTeam1 = i;
                strcpy(newSchedule.idTeam1, (team + indexTeam1)->teamID);
            }
        }
        if (indexTeam1 != -1)
        {
            break;
        }
        else
        {
            printf("Khong tim thay ten doi nay!!\nMoi nhap lai ten doi 1 : ");
        }
    }

    printf("| ten doi thu 2 : ");
    while (1)
    {
        fflush(stdin);
        scanf("%[^\n]s", newSchedule.nameTeam2);
        for (int i = 0; i < teamCount; i++)
        {
            if (strcmp(newSchedule.nameTeam2, (team + i)->teamName) == 0 && strcmp(newSchedule.nameTeam1, newSchedule.nameTeam2) != 0)
            {
                indexTeam2 = i;
                strcpy(newSchedule.idTeam2, (team + indexTeam2)->teamID);
            }
        }
        if (indexTeam2 != -1)
        {
            break;
        }
        else
        {
            printf("Khong tim thay ten doi nay hoac trung voi ten doi 1!!\nMoi nhap lai ten doi 2 : ");
        }
    }
    ////////////////////////////////////
    printf("| Nhap Ngay Thi Dau(dd/mm/yyyy) : ");
    while (1)
    {
        int check = 0;

        fflush(stdin);
        scanf("%[^\n]s", date);
        if (strlen(date) <= 10)
        {
            for (int i = 0; i < 10; i++)
            {
                if ((date[2] == '/' && date[5] == '/') || (date[i] >= '0' && date[i] <= '9'))
                {
                    check++;
                }
                else
                {
                    check = 0;
                    break;
                }
            }
            if (check != 0)
            {
                strcpy(newSchedule.ngayDau, date);
                break;
            }
            else
            {
                printf("Moi nhap lai: ");
            }
        }
        else
        {
            printf("Moi nhap lai: ");
        }
    }
    printf("| Nhap Gio Thi Dau : ");
    while (1)
    {
        fflush(stdin);
        scanf("%[^\n]s", newSchedule.gioDau);
        int checkGD = checkInputSpecialCharacter(newSchedule.gioDau);
        if (checkGD == 1)
        {
            break;
        }
        else
        {
            printf("Moi nhap lai gio thi dau: ");
        }
    }
    printf("| Nhap San : ");
    while (1)
    {
        int check = 0;
        fflush(stdin);
        scanf("%[^\n]s", newSchedule.sanDau);
        for (int i = 0; i < strlen(newSchedule.sanDau); i++)
        {
            if ((newSchedule.sanDau[i] >= 'a' && newSchedule.sanDau[i] <= 'z') || (newSchedule.sanDau[i] >= 'A' && newSchedule.sanDau[i] <= 'Z') && newSchedule.sanDau[0] != '\n')
            {
                check++;
            }
            else
            {
                if (newSchedule.sanDau[i] == ' ')
                {
                    check++;
                }
                else
                {
                    check = 0;
                    break;
                }
            }
        }
        if (check > 0)
        {
            break;
        }
        else
        {
            printf("Moi nhap lai san dau: ");
        }
    }
    return newSchedule;
}

void printSchedule()
{
    fflush(stdin);

    // fflush(stdin);
    // ReadTeamsFromFile("VL2018Teams.dat", &teamCount, team);
    fflush(stdin);
    int indexTeam1 = -1;
    int indexTeam2 = -1;
    system("cls");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|                                                               Lich Thi Dau                                                               |\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-20s | %-30s | %-25s | %-25s | %-24s |\n", "Tran", "Tran Dau", "Ngay Thi Dau", "Gio Thi Dau", "San Thi Dau");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------\n");
    ReadScheduleFromFile("VL2018Schedules.dat", &scheduleCount, schedule);
    for (int i = 0; i < scheduleCount; i++)
    {
        for (int j = 0; j < teamCount; j++)
        {
            if (strcmp((schedule + i)->idTeam1, (team + j)->teamID) == 0)
            {
                indexTeam1 = j;
            }
            if (strcmp((schedule + i)->idTeam2, (team + j)->teamID) == 0)
            {
                indexTeam2 = j;
            }
        }

        printf("| %-20s | %-15s%-4s%11s | %-25s | %-25s | %-24s |\n", (schedule + i)->tranDau, (team + indexTeam1)->teamName, " vs ", (team + indexTeam2)->teamName, (schedule + i)->ngayDau, (schedule + i)->gioDau, (schedule + i)->sanDau);
    }
    printf("--------------------------------------------------------------------------------------------------------------------------------------------\n");
    fflush(stdin);
}

void KQTD()
{

    int indexTranDau = -1;
    ReadTeamsFromFile("VL2018Log.dat", &teamCount, team);
    int pointTeam1 = -1, pointTeam2 = -1;
    char nameteam1[100], nameteam2[100];
    int indexTeam1 = -1, indexTeam2 = -1;

    while (1)
    {
        system("cls");
        printSchedule();
        char tranDau[100];
        printf("--------Ket qua tran dau--------\n");
        printf("Tran : ");
        while (1)
        {
            fflush(stdin);
            scanf("%[^\n]s", tranDau);
            for (int i = 0; i < scheduleCount; i++)
            {
                if (strcmp(tranDau, (schedule + i)->tranDau) == 0)
                {
                    indexTranDau = i;
                    break;
                }
            }
            for (int i = 0; i < teamCount; i++)
            {
                if (strcmp((schedule + indexTranDau)->idTeam1, (team + i)->teamID) == 0)
                {
                    indexTeam1 = i;
                }
                if (strcmp((schedule + indexTranDau)->idTeam2, (team + i)->teamID) == 0)
                {
                    indexTeam2 = i;
                }
            }

            if (indexTranDau != -1 && tranDau[0] != '\n')
            {
                printf("Tran dau giua : %s vs %s \n", (team + indexTeam1)->teamName, (team + indexTeam2)->teamName);
                break;
            }
            else
            {
                printf("Co ki tu dac biet hoac khong co tran dau nay!!!\nMoi Nhap lai tran dau: ");
            }
        }

        while (1) //Check định dạng nhập có phải %d hay không
        {
            printf("Ket Qua %s : ", (team + indexTeam1)->teamName);
            int check = scanf("%d", &pointTeam1);
            if (check == 1 && pointTeam1 >= 0)
            {
                break;
            }
            else
            {
                printf("Sai dinh dang cua %%d !\nNhap 1 phim bat ki de nhap lai...");
                fflush(stdin);
                getchar();
            }
        }
        while (1) //Check định dạng nhập có phải %d hay không
        {
            printf("Ket Qua %s : ", (team + indexTeam2)->teamName);
            int check = scanf("%d", &pointTeam2);
            if (check == 1 && pointTeam2 >= 0)
            {
                break;
            }
            else
            {
                printf("Sai dinh dang %%d !\nNhap 1 phim bat ki de nhap lai...");
                fflush(stdin);
                getchar();
            }
        }

        printf("Ban co muon cap nhat(y/n)? ");
        char yn = checkYN(yn);
        if (yn == 'y' || yn == 'Y')
        {
            (team + indexTeam1)->tongTran++;
            (team + indexTeam2)->tongTran++;
            if (pointTeam1 > pointTeam2)
            {
                (team + indexTeam1)->thang++;
                (team + indexTeam2)->thua++;
            }
            else if (pointTeam2 > pointTeam1)
            {
                (team + indexTeam2)->thang++;
                (team + indexTeam1)->thua++;
            }
            if (pointTeam2 == pointTeam1)
            {
                (team + indexTeam1)->hoa++;
                (team + indexTeam2)->hoa++;
            }
            printf("ket qua tran dau da duoc cap nhat!");
            fflush(stdin);
            WriteTeamsToFile(team, teamCount, "VL2018Log.dat");
            getchar();
            break;
        }
        break;
    }
}

void thongKe()
{
    // fflush(stdin);
    // ReadTeamsFromFile("VL2018Teams.dat", &teamCount, team);
    fflush(stdin);
    ReadTeamsFromFile("VL2018Log.dat", &teamCount, team);
    for (int i = 0; i < teamCount; i++)
    {
        int thang = (team + i)->thang;
        int hoa = (team + i)->hoa;
        int thua = (team + i)->thua;
        (team + i)->tongdiem = (thang * 3) + hoa;
    }
    for (int i = 0; i < teamCount - 1; i++)
    {
        for (int j = i + 1; j < teamCount; j++)
        {
            if ((team + j)->tongdiem > (team + i)->tongdiem)
            {
                struct doiBong temp = *(team + i);
                *(team + i) = *(team + j);
                *(team + j) = temp;
            }
        }
    }
    // sapxepBXH();
    system("cls");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("|                                                       BXH                                                            |\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-10s | %-10s | %-25s | %-10s | %-10s | %-10s | %-10s | %-10s |\n", "Xep Hang", "Ma Doi", "Ten Doi", "Tran", "Thang", "Thua", "Hoa", "Diem");
    for (int i = 0; i < teamCount; i++)
    {
        printf("| %-10d | %-10s | %-25s | %-10d | %-10d | %-10d | %-10d | %-10d |\n", i + 1, (team + i)->teamID, (team + i)->teamName, (team + i)->tongTran, (team + i)->thang, (team + i)->thua, (team + i)->hoa, (team + i)->tongdiem);
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("An 1 phim bat ki...");
    fflush(stdin);
    // WriteTeamsToFile(team, teamCount, "VL2018Log.dat");
    getchar();
}
int ReadTeamsFromFile(char *fileName, int *pCount, struct doiBong *pListStudents)
{
    FILE *pf;
    int result = 0;

    pf = fopen(fileName, "rb");

    if (pf != NULL)
    {
        //Đọc số struct Student lưu trong file
        fread(pCount, sizeof(int), 1, pf);
        if (pCount > 0)
        {
            //Đọc dữ liệu của các struct Student trong file
            //rồi lưu vào pListStudents
            fread(pListStudents, sizeof(struct doiBong), *pCount, pf);
            result = 1;
        }

        //Đóng file
        fclose(pf);
    }

    return result;
}

int WriteTeamsToFile(struct doiBong *pListStudents, int count, char *fileName)
{
    FILE *pf;

    int result = 0;

    pf = fopen(fileName, "wb");

    if (pf != NULL)
    {
        //Ghi số lượng struct Student vào đầu file
        fwrite(&count, sizeof(int), 1, pf);

        //Ghi mảng các struct Student vào file
        fwrite(pListStudents, sizeof(struct doiBong), count, pf);
        fclose(pf);
        result = 1;
    }

    return result;
}
int ReadScheduleFromFile(char *fileName, int *pCount, struct schedule *pListStudents)
{
    FILE *pf;
    int result = 0;

    pf = fopen(fileName, "rb");
    if (pf != NULL)
    {
        //Đọc số struct Student lưu trong file
        fread(pCount, sizeof(int), 1, pf);
        if (pCount > 0)
        {
            //Đọc dữ liệu của các struct Student trong file
            //rồi lưu vào pListStudents
            fread(pListStudents, sizeof(struct schedule), *pCount, pf);
            result = 1;
        }

        //Đóng file
        fclose(pf);
    }

    return result;
}

int WriteScheduleToFile(struct schedule *pListStudents, int count, char *fileName)
{
    FILE *pf;

    int result = 0;

    pf = fopen(fileName, "wb");

    if (pf != NULL)
    {
        //Ghi số lượng struct Student vào đầu file
        fwrite(&count, sizeof(int), 1, pf);

        //Ghi mảng các struct Student vào file
        fwrite(pListStudents, sizeof(struct schedule), count, pf);
        fclose(pf);
        result = 1;
    }

    return result;
}
