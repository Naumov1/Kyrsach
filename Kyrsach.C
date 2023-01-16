#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <conio.h>
#include <stddef.h>
#include <stdlib.h>

int new_zapisi(zapis, chislo_zapis);
int pechat(zapis, chislo_zapis,i);
int* poisk(zapis, chislo_zapis, number_poisk, name_poisk, mas_ind);
int* poisk_sec(zapis, chislo_zapis, number_poisk, mas_ind);
void sohr(zapis, chislo_zapis);
int read(zapis, chislo_zapis);
void sort(zapis, chislo_zapis);
void redakt(zapis, number, chislo_zapis);
int compare_sek( av, bv);

struct database {
	int number;
	char tema[50];
	char FIO[50];
	int poradok;
	int min;
	int data[3];
};
typedef struct database kp;

int main() {
	setlocale(LC_ALL, "rus");
	system("chcp 1251");
	int g = 1, z;
	FILE* out;
	int chislo_zapis = 0;
	kp* zapis = NULL;
	int p;
	int number_poisk;
	char name_poisk[50];

	printf("Выберите пункт\n");
	while (g != 0) {
		printf("1)Добавить новую строку\n2)Вывод записей\n3)Поиск по критериям\n4)сортировка\n5)Изменить запись\n0)выход\n");
		scanf("%d", &z);
		switch (z) {
		case 1:
			zapis = realloc(zapis, (chislo_zapis + 1) * sizeof(kp));

			chislo_zapis = new_zapisi(zapis, chislo_zapis);

			int o_f = 2;   
			sohr(zapis, chislo_zapis - 1, o_f);
			break;
		case 2:
			out = fopen("kp.txt", "r");

			int str = 0;
			while (!feof(out))
			{
				if (fgetc(out) == '\n')
					str++;
			}
			str = str / 4;
			zapis = (kp*)malloc(str * sizeof(kp));

			chislo_zapis = read(zapis, chislo_zapis);
			printf("|Дата научного доклада|  Секции  |            тема доклада            |                       Ф.И.О                        |Регламент в минутах|\n");
			for (int i = 0;i < chislo_zapis;i++) {
				//printf("-----------запись %d------------\n", i + 1);
				pechat(zapis[i]);
			}
			break;
		case 3:
			printf("Выберите поиск:\n1-по ФИО и номеру секции\n2-по номеру секции\n");
			scanf("%d", &p);
			int* mas_ind = malloc(chislo_zapis * sizeof(kp));	

			if (p == 1)
			{
				printf("Введите Ф.И.О\n");
				getchar();
				fgets(name_poisk, 50, stdin);
				printf("Введите # секции\n");
				scanf("%d", &number_poisk);
				mas_ind = poisk(zapis, chislo_zapis, number_poisk, name_poisk, mas_ind);

				for (int i = 0; i < chislo_zapis; i++)
					if (mas_ind[i] == 1) pechat(zapis[i]);
			}
			else if (p == 2)
			{
				printf("Введите # секции\n");
				scanf("%d", &number_poisk);
				mas_ind = poisk_sec(zapis, chislo_zapis, number_poisk, mas_ind);

				for (int i = 0; i < chislo_zapis; i++)
					if (mas_ind[i] == 1) pechat(zapis[i]);
			}
			break;
		case 4:
			chislo_zapis = read(zapis, chislo_zapis);
			sort(zapis, chislo_zapis);
			break;
		case 5:
		{
			int number;
			printf("Введите номер записи, которую хотите изменить\n");
			scanf("%d", &number);
			getchar();
			number--;

			chislo_zapis = read(zapis, chislo_zapis);
			redakt(zapis, number, chislo_zapis);

			for (int i = 0; i < chislo_zapis; i++)
			{
				if (i == 0) sohr(zapis, i, 1);
				else sohr(zapis, i, 2);
			}
			break;
		}
		case 0:
			g = 0;
			break;
		}
	}
}
int new_zapisi(kp* zapis, int chislo_zapis) {
	printf("Дата научного доклада\n");
	scanf("%d.%d.%d", &zapis[chislo_zapis].data[0], &zapis[chislo_zapis].data[1], &zapis[chislo_zapis].data[2]);
	getchar();

	printf("# Секции\n");
	scanf("%d", &zapis[chislo_zapis].number);
	getchar();

	printf("тема доклада\n");
	fgets(zapis[chislo_zapis].tema, 50, stdin);

	printf("Фамилия Имя Отчество\n");
	fgets(zapis[chislo_zapis].FIO, 50, stdin);

	printf("Регламент в минутах\n");
	scanf("%d", &zapis[chislo_zapis].min);

	chislo_zapis++;
	return chislo_zapis;
}
int pechat(kp zapis) {
	/*printf("|Дата научного доклада|  Секции  |            тема доклада            |                       Ф.И.О                        |Регламент в минутах|\n");*/
	printf("-------------------------------------------------------------------------------------------------------------------------------------------------|\n");
		printf("|%5d.%d.%4d", zapis.data[0], zapis.data[1], zapis.data[2]);
		printf("%15d", zapis.number);
		printf("%30s", zapis.tema);
		printf("%50s", zapis.FIO);
		printf("%25dmin\n", zapis.min);
}
int* poisk(kp* zapis, int chislo_zapis, int number_poisk, char* name_poisk) {
	for (int i = 0; i <= chislo_zapis; i++) {
		if (strcmp(name_poisk, zapis[i].FIO) == 0 && (number_poisk == zapis[i].number)) return i;
	}
	 return -1;
}
int* poisk_sec(kp* zapis, int chislo_zapis, int number_poisk, int* mas_ind) {
	for (int i = 0; i <= chislo_zapis; i++)
	{
		if (number_poisk == zapis[i].number) mas_ind[i] = 1;
		else mas_ind[i] = 0;
	}
	return mas_ind;
}

void sohr(kp* zapis, int chislo_zapis, int o_f)
{
	FILE* out;
	if (o_f == 1) out = fopen("kp.txt", "w");
	else out = fopen("kp.txt", "a");

	fprintf(out, "\n%d ", zapis[chislo_zapis].data[0]);
	fprintf(out, "%d ", zapis[chislo_zapis].data[1]);
	fprintf(out, "%d\n", zapis[chislo_zapis].data[2]);
	fprintf(out, "%d\n", zapis[chislo_zapis].number);
	fprintf(out, "%s", zapis[chislo_zapis].tema);
	fprintf(out, "%s", zapis[chislo_zapis].FIO);
	fprintf(out, "%d", zapis[chislo_zapis].min);

	fclose(out);
}
int read(kp* zapis, int chislo_zapis) {
	int i = 0;
	FILE* out;
	char b[50];

	out = fopen("kp.txt", "r");
	while (!feof(out)) {
		fscanf(out, "%d", &zapis[i].data[0]);
		fscanf(out, "%d", &zapis[i].data[1]);
		fscanf(out, "%d\n", &zapis[i].data[2]);
		fscanf(out, "%d\n", &zapis[i].number);
		fgets(zapis[i].tema, 50, out);
		strtok(zapis[i].tema, "\n");
		printf("\n");
		fgets(zapis[i].FIO, 50, out);
		strtok(zapis[i].FIO, "\n");
		printf("\n");
		fscanf(out, "%d\n", &zapis[i].min);
		i++;
	}
	fclose(out);
	return i;
}
void sort(kp* zapis, int chislo_zapis) {
	qsort(zapis, chislo_zapis, sizeof(kp), compare_sek);
	int *count = malloc(sizeof(kp) * chislo_zapis);
	int *array = malloc(sizeof(kp) * chislo_zapis);
		for (int i = 0; i < chislo_zapis; i++) {
			array[zapis[i].number] = 0;
			count[zapis[i].number] = 0;
		}

	for (int i = 0; i < chislo_zapis; i++) {
		array[zapis[i].number] += zapis[i].min;
		count[zapis[i].number]++;
	}

	for (int i = 0; i < chislo_zapis; i++) {
		if (array[zapis[i].number] > 0) {
			pechat(zapis[i]);
			if (zapis[i].number!=zapis[i+1].number)
				printf("-----------------------------\n");
			printf("Среднее время секции %d = %g\n", zapis[i].number, (float)(array[zapis[i].number]) / count[zapis[i].number]);

		}
	}
}

void redakt(kp* zapis, int number, int chislo_zapis)
{
	if (number >= chislo_zapis) {
		printf("Запись не найдена\n");
		return NULL;
	}

	new_zapisi(zapis, number);
}
int compare_sek(const void* av, const void* bv) 
{
	const kp* a = av, * b = bv;
	if (a->number > b->number)return 1;
	if (a->number < b->number)return -1;
	if (a->min > b->min)return 1;
	if (a->min < b->min)return -1;
	return 0;
}
