#include "User.h"
#include "Initialization.h"
#include <direct.h>
#include <errno.h>
#include <stdio.h>
#include <cstring>

void InputDataCh(char arr[33])
{
	string temp = "";
	do
	{
		while (temp == "") getline(cin, temp);
		if (cin.fail() || temp.size() > 33)
		{
			cin.clear();

			temp = "";
			cout << "Fail input! Try again!" << endl;
		}
		else break;
	} while (true);

	for (int i = 0; i < temp.size(); i++) arr[i] = temp[i];
}

void InputDataChN(char arr[20])
{
	string temp = "";
	do
	{
		while (temp == "") getline(cin, temp);
		if (cin.fail() || temp.size() > 20)
		{
			cin.clear();

			temp = "";
			cout << "Fail input! Try again!" << endl;
		}
		else break;
	} while (true);

	for (int i = 0; i < temp.size(); i++) arr[i] = temp[i];
}

void Registration()
{
	cout << "Login is restricted up to 20 symbols, password up to 32 symbols!" << endl << endl;
	char name[20] = { "\0" }, login[33] = { " " }, password[33] = { " " };
	cout << "Login: ";
	while (login[0] == ' ') InputDataCh(login);
	cout << endl << "Password: ";
	while (password[0] == ' ') InputDataCh(password);
	cout << endl << "Name: ";
	do InputDataChN(name); while (name[0] == ' ' && isNameCorrect(name));
	Role studRole;
	int temp = 0;
	cout << endl << "Chose your role: \n1 - New Student;\n2 - Admin" << endl;
	do
	{
		cin >> temp;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore('\n', 32747);
			cout << "Fail input! Try again! (1 or 2)" << endl;
		}
		if (temp != 1 && temp != 2) cout << "Fail input! Try again! (1 or 2)" << endl;
	} while (temp != 1 && temp != 2);
	studRole = (Role)(temp - 1);

	Student obj, temp2;
	bool result = TryFindUser(login, temp, obj);
	if (!result) TryCreateUser(login, password, name, studRole, temp2);
	else
	{
		cout << "This login is not available" << endl;
		return;
	}
}

void Login()
{
	char login[33] = { " " }, password[33] = { " " };
	cout << "Login: ";
	while (login[0] == ' ') InputDataCh(login);
	cout << endl << "Password: ";
	while (password[0] == ' ') InputDataCh(password);
	Role role = Admin;

	Student obj;
	if (TryLogin(login, password, role, obj))
	{
		if (role == NewUser) LoginUserMenu(obj);
		else LoginAdminMenu();
		return;
	}
	else
	{
		cout << "Incorrect Login or Password!" << endl;
		return;
	}
	return;
}

void LoginAdminMenu()
{
	system("cls");
	Init start(int(1));
	start.Show_Lab();
}

void Create()
{
	char name[20] = { "Tree" }, login[33] = { " " }, password[33] = { "T" };
	int pos = 0;
	Student temp, obj;

	cout << "Attantion if you write more then 20 symbols in name of Tree, it will be cuted" << endl << endl;
	cout << "Name/Login of Tree: ";
	while (obj.login[0] == '\0') InputDataCh(obj.login);
	if (TryFindUser(obj.login, pos, temp))
	{
		cout << "Login is exist! Error!" << endl;
		return;
	}

	Role tree = Tree;

	TryCreateUser(obj.login, password, name, tree, temp);
	SetUp(temp);
}

void Show()
{
	FILE* fp;
	if ((fp = fopen("mail", "rb")) == NULL) {
		cout << "Results is not avaible now, wait!" << endl;
		return;
	}

	_Q *que = new _Q();
	Student *obj = new Student();

	std::ifstream in_file("mail", std::ios::binary | std::ios::ate);
	int file_size = in_file.tellg();

	if (file_size != 0)
	{
		for (int i = 0; i < file_size / sizeof(Student); i++)
		{

			fseek(fp, i * sizeof(Student), 0);
			fread(obj, sizeof(Student), 1, fp);
			if (obj->role == Tree)
			{
				TryFindUserData(obj->FKid, *que);

				for (unsigned int i = 0; i < 40; i++) cout << "=";
				cout << endl << *obj << *que;
			}
		}
	}

	for (unsigned int i = 0; i < 40; i++) cout << "=";
	cout << endl;
	_fcloseall();
	fclose(fp);
	delete obj;
	delete que;
	return;
}

void Update()
{
	char login[33] = { " " }, name[20] = { " " };;
	cout << "Login: ";
	while (login[0] == ' ') InputDataCh(login);

	char bufL[33];
	string tmpL = md5(login);

	int position = 0, temp = 0;
	Student obj;
	_Q que;
	if (TryFindUser(login, position, obj))
	{
		cout << "What do you want to change? UserInfo(Name) or Marks(1 or 2)?" << endl;
		do
		{
			cin >> temp;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore('\n', 32747);
				cout << "Fail input! Try again! (1 or 2)" << endl;
			}
			if (temp != 1 && temp != 2) cout << "Fail input! Try again! (1 or 2)" << endl;
		} while (temp != 1 && temp != 2);
		switch (temp)
		{
		case 1:
			cout << endl << "Name: ";
			while (name[0] == ' ')
			{
				InputDataChN(name);
				if (!isNameCorrect(name) && name[0] != ' ') name[0] = ' ';
			}
			for (int i = 0; i < 33; i++) bufL[i] = tmpL[i];
			DeleteUserInfo(bufL);
			if (!TryUpdate(obj.login, obj.password, name, obj.role, obj.isEntrInfo, obj.FKid)) cout << "Error!" << endl;
			break;
		case 2:
			if (TryFindUserData(obj.FKid, que))
			{
				DeleteMarks(obj.FKid);
				obj.isEntrInfo = false;
				SetUp(obj);
			}
			else
			{
				obj.isEntrInfo = false;
				SetUp(obj);
			}
			break;
		}
	}
	else cout << "Login is no correct!" << endl;
}

void Delete()
{
	char login[33] = { "" };
	cout << "Login: ";
	do InputDataCh(login); while (login[0] == ' ' && login[0] == '\0');

	int pos = 0;
	Student obj;

	char bufL[33];
	string tmpL = md5(login);
	for (int i = 0; i < 33; i++) bufL[i] = tmpL[i];

	if (TryFindUser(login, pos, obj))
	{
		DeleteUserInfo(bufL);
		DeleteMarks(obj.FKid);
	}
}

void DeleteUserInfo(char login[33])
{
	if (login[0] == ' ') cout << "Login: ";
	while (login[0] == ' ') InputDataCh(login);

	int position = 0;
	Student obj, obj2;

	if (TryFindUserMD5(login, position, obj2))
	{
		int pos = GetPositionUserInfo(login);

		FILE* fpR, * fpW;
		if ((fpR = fopen("mail", "r+b")) == NULL) {
			printf("Cannot open file.\n");
			exit(1);
		}
		if ((fpW = fopen("mail2", "a+b")) == NULL) {
			printf("Cannot open file.\n");
			exit(1);
		}

		std::ifstream in_file("mail", std::ios::binary | std::ios::ate);
		int file_size = in_file.tellg();

		if (file_size != 0)
			for (int i = 0, j = 0; i < file_size / sizeof(Student); i++)
			{
				fseek(fpR, i * sizeof(Student), 0);
				fread(&obj, sizeof(Student), 1, fpR);
				if (!(strcmp(obj.login, obj2.login) == 0 && obj.FKid == obj2.FKid)) 
					fwrite(&obj, sizeof(struct Student), 1, fpW);
			}

		fclose(fpR);
		fclose(fpW);
		_fcloseall();

		remove("mail") != 0 ? cout << "Error: " << strerror(errno) << endl : cout << "Ok..." << endl;

		rename("mail2", "mail") != 0 ? cout << "Error: " << strerror(errno) << endl : cout << "Ok..." << endl;
	}
	else cout << "Login is no correct!" << endl;
}

void DeleteMarks(int id)
{
	_fcloseall();
	try
	{
		_Q obj, obj2;

		if (TryFindUserData(id, obj2))
		{
			FILE* fpR, * fpW;
			if ((fpR = fopen("post", "r+b")) == NULL) {
				printf("Cannot open file.\n");
				exit(1);
			}
			if ((fpW = fopen("post2", "a+b")) == NULL) {
				printf("Cannot open file.\n");
				exit(1);
			}

			std::ifstream in_file("post", std::ios::binary | std::ios::ate);
			int file_size = in_file.tellg();

			if (file_size != 0)
				for (int i = 0, j = 0; i < file_size / sizeof(_Q); i++)
				{
					fseek(fpR, i * sizeof(_Q), 0);
					fread(&obj, sizeof(_Q), 1, fpR);
					if (obj.id != obj2.id)
						fwrite(&obj, sizeof(struct _Q), 1, fpW);
				}

			fclose(fpR);
			fclose(fpW);
			_fcloseall();

			remove("post") != 0 ? cout << "Error" << endl : cout << "Ok..." << endl;

			rename("post2", "post") != 0 ? cout << "Error" << endl : cout << "Ok..." << endl;
		}
	}
	catch (const std::exception& e)
	{
	}
	
	return;
}

void LoginUserMenu(Student& obj)
{
	system("cls");
	Show();
	return;
}

void SetUp(Student& obj)
{
	if (!obj.isEntrInfo)
	{
		system("cls");
		_Q que;
		cout << "X: ";
		que.x = InputMark();
		cout << endl << "Y: ";
		que.y = InputMark();
		cout << endl << "Age: ";
		que.age = InputMark();
		cout << endl << "Type: ";
		InputDataCh(que.type);
		while (cin.fail())
		{
			cin.clear();
			cin.ignore('\n', 32747);
			cout << "Fail input! Try again!" << endl;
			cin >> que.type;
		}
		que.id = obj.FKid;
		//cout << que.id << endl << endl;
		DeleteUserInfo(obj.login);
		if (!TryUpdate(obj.login, obj.password, obj.name, obj.role, true, que.id)) cout << "Error!" << endl;
		if (!TrySaveUserData(que)) cout << "Error!" << endl;
	}
}

int InputMark()
{
	int temp;
	do
	{
		cin >> temp;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore('\n', 32747);
			cout << "Fail input! Try again! (1-200)" << endl;
		}
		if (temp < 1 || temp > 200) cout << "Fail input! Try again! (1-200)" << endl;
	} while (temp < 1 || temp > 200);
	return temp;
}


int GetPositionUserInfo(char login[33])
{
	FILE* fp;
	if ((fp = fopen("mail", "rb")) == NULL) {
		printf("Cannot open file.\n");
		exit(1);
	}

	Student obj;

	std::ifstream in_file("mail", std::ios::binary | std::ios::ate);
	int file_size = in_file.tellg();

	if (file_size != 0)
	{
		for (int i = 0; i < file_size / sizeof(Student); i++)
		{
			fseek(fp, i * sizeof(Student), 0);
			fread(&obj, sizeof(Student), 1, fp);
			char buf2[33];
			for (int i = 0; i < 33; i++) buf2[i] = obj.login[i];
			if (strcmp(login, buf2) == 0)
			{
				fclose(fp);
				return obj.FKid;
			}
		}
	}

	fclose(fp);
	return -1;
}

bool TryUpdate(char login[33], char passsword[32], char name[20], Role role, bool isEnteredInfo, int id)
{

	FILE* fp;
	if ((fp = fopen("mail", "a+b")) == NULL) {
		printf("Cannot open file.\n");
		exit(1);
	}

	Student* obj = new Student;

	for (int i = 0; i < 33; i++) {
		obj->login[i] = login[i];
		obj->password[i] = passsword[i];
		if (i < 20) obj->name[i] = name[i];
		if (i == 0) obj->role = role;
	}

	obj->isEntrInfo = isEnteredInfo;
	obj->FKid = id;

	fwrite(obj, sizeof(struct Student), 1, fp);
	fclose(fp);

	return true;
}

bool TryLogin(char login[33], char passsword[32], Role& role, Student& obj)
{
	FILE* fp;
	if ((fp = fopen("mail", "rb")) == NULL) {
		printf("Cannot open file.\n");
		exit(1);
	}

	char bufL[33], bufP[33];

	string tmpL = md5(login), tmpP = md5(passsword);

	for (int i = 0; i < 33; i++)
	{
		bufL[i] = tmpL[i];
		bufP[i] = tmpP[i];
	}

	std::ifstream in_file("mail", std::ios::binary | std::ios::ate);
	int file_size = in_file.tellg();

	if (file_size != 0)
	{
		for (int i = 0; i < file_size / sizeof(Student); i++)
		{
			fseek(fp, i * sizeof(Student), 0);
			fread(&obj, sizeof(Student), 1, fp);
			char bufL2[33], bufP2[33];
			Role bufR2;
			for (int i = 0; i < 33; i++)
			{
				bufL2[i] = obj.login[i];
				bufP2[i] = obj.password[i];
				if (i == 0) bufR2 = obj.role;
			}
			if (strcmp(bufL, bufL2) == 0 && strcmp(bufP, bufP2) == 0)
			{
				role = bufR2 == Admin ? Admin : NewUser;
				fclose(fp);
				return true;
			}
		}
	}


	fclose(fp);
	return false;
}

bool TryFindUser(char login[33], int& position, Student& obj)
{
	FILE* fp;
	if ((fp = fopen("mail", "rb")) == NULL) {
		printf("Cannot open file.\n");
		exit(1);
	}

	char buf[33];
	string tmp = md5(login);

	for (int i = 0; i < 33; i++) buf[i] = tmp[i];

	std::ifstream in_file("mail", std::ios::binary | std::ios::ate);
	int file_size = in_file.tellg();

	if (file_size != 0)
	{
		for (int i = 0; i < file_size / sizeof(Student); i++)
		{
			fseek(fp, i * sizeof(Student), 0);
			fread(&obj, sizeof(Student), 1, fp);
			char buf2[33];
			for (int i = 0; i < 33; i++) buf2[i] = obj.login[i];
			if (strcmp(buf, buf2) == 0)
			{
				position = i;
				fclose(fp);
				return true;
			}
		}
	}


	fclose(fp);
	return false;
}

bool TryFindUserMD5(char login[33], int& position, Student& obj)
{
	FILE* fp;
	if ((fp = fopen("mail", "rb")) == NULL) {
		printf("Cannot open file.\n");
		exit(1);
	}

	std::ifstream in_file("mail", std::ios::binary | std::ios::ate);
	int file_size = in_file.tellg();

	if (file_size != 0)
	{
		for (int i = 0; i < file_size / sizeof(Student); i++)
		{
			fseek(fp, i * sizeof(Student), 0);
			fread(&obj, sizeof(Student), 1, fp);
			char buf2[33];
			for (int i = 0; i < 33; i++) buf2[i] = obj.login[i];
			if (strcmp(login, buf2) == 0)
			{
				position = i;
				fclose(fp);
				return true;
			}
		}
	}


	fclose(fp);
	return false;
}

bool TryCreateUser(char login[33], char passsword[33], char name[20], Role role, Student& refObj)
{
	FILE* fp;
	if ((fp = fopen("mail", "a+b")) == NULL) {
		printf("Cannot open file.\n");
		exit(1);
	}

	Student* obj = new Student();

	string tmpLogin = md5(login), tmpPassword = md5(passsword);

	for (int i = 0; i < 33; i++) {
		obj->login[i] = tmpLogin[i];
		obj->password[i] = tmpPassword[i];
		if (i < 20) obj->name[i] = name[i];
		if (i == 0) obj->role = role;
	}

	obj->FKid = SetId();
	fwrite(obj, sizeof(struct Student), 1, fp);
	fclose(fp);
	refObj = *obj;
	return true;
}

bool TrySaveUserData(_Q que)
{
	FILE* fp;
	if ((fp = fopen("post", "a+b")) == NULL) {
		printf("Cannot open file.\n");
		exit(1);
	}

	_Q* q = new _Q(que.age, que.x, que.y, que.type, que.id);

	fwrite(q, sizeof(struct _Q), 1, fp);
	fclose(fp);

	return true;
}

bool TryFindUserData(int id, _Q& obj)
{
	FILE* fp;
	if ((fp = fopen("post", "rb")) == NULL) {
		printf("Cannot open file.\n");
		exit(1);
	}

	std::ifstream in_file("post", std::ios::binary | std::ios::ate);
	int file_size = in_file.tellg();

	if (file_size != 0)
	{
		for (int i = 0; i < file_size / sizeof(_Q); i++)
		{
			fseek(fp, i * sizeof(_Q), 0);
			fread(&obj, sizeof(_Q), 1, fp);
			if (id == obj.id)
			{
				fclose(fp);
				return true;
			}
		}
	}

	fclose(fp);
	return false;
}

int strlength(char* str)
{
	int i = 0;
	while (str[i] != '\0') i++;
	return i;
}

bool isNameCorrect(char* name)
{
	if (strlength(name) == 0) return false;
	for (int i = 0; i < strlength(name); i++)
		if (!isalpha(name[i]))
		{
			cout << "Incorrect Name Input!" << endl;
			return false;
		}
	return true;
}
