/*

 ∧＿＿∧
(。・ω・)つー☆・ * 。
⊂     ノ         .  ゜
し————Ｊ      Accepted

*/

#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/STACK:108777216")

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>
#include <Windows.h>

using ll = long long;
using ull = unsigned long long;
using ld = long double;
//�KAN
//template<typename T>
//using pair2<T> = pair<T, T>;

#define forn(i, a, b) for (int i = a; i < b; i++)
#define form(i, a, b) for (int i = a - 1; i >= b; i--)
#define all(a) a.begin(), a.end()
#define input input_______

template<typename T, typename U> static void amin(T &x, U y) { if (y < x) x = y; }
template<typename T, typename U> static void amax(T &x, U y) { if (x < y) x = y; }

using namespace std;

static const int INF = 0x3f3f3f3f; static const long long INFL = 0x3f3f3f3f3f3f3f3fLL; static const long long LOL = 0xabacabadabacabaLL;

struct country {
	string name;
	string capital;

	bool operator <(const country &c) const {
		return capital < c.capital;
	}
};

struct user {
	string name;
	string pass;
	ull solved;
	ull sum;

	bool operator < (const user &u) const {
		return name < u.name;
	}
};

int seed, a, b, m;
int random() {
	ofstream out("random.ota");
	seed = ((ll)seed * (ll)a + (ll)b) % m;
	out << seed;
	return seed;
}

void setrandom() {
	ifstream in("random.ota");
	in >> seed;
	//a = 1203;
	//b = 1020;
	a = 239;
	b = 9997;
	m = (int)1e9 + 7;
}

vector<country> E;
vector<country> SA;
vector<country> NA;
vector<country> AF;
vector<country> AS;
vector<country> AU;

void game1();
void game2();
void game3();
void game4();

void input(vector<country> &a, string name) {
	name += ".in";
	ifstream in(name);

	string s;
	while (getline(in, s)) {
		string t;
		getline(in, t);
		a.push_back({ t, s });
	}
}

set<user> users;
void get_users() {
	ifstream in("user.ota");
	string n;
	while (in >> n) {
		string p;
		ull so, su;
		in >> p >> so >> su;

		users.insert({ n, p, so, su });
	}
}

bool durashka = false;
void status(ull so, ull su);

void update_user(string &s, int new_sol, int new_sum) {
	if (s == "Not a user")
		return;

	auto it = users.begin();
	while (it != users.end() && it->name != s)
		it++;

	user curr_user = *it;
	users.erase(it);
	curr_user.sum += new_sum;
	curr_user.solved += new_sol;
	users.insert(curr_user);

	cout << "Ваши текущие результаты обновлены\n";

	ofstream out("user.ota");
	for (auto &i : users)
		out << i.name << ' ' << i.pass << ' ' << i.solved << ' ' << i.sum << '\n';

	status(curr_user.solved, curr_user.sum);
}

void status(ull so, ull su) {
	if (so == 0 && su == 0) {
		cout << "Не в рейтинге\n";
		return;
	}
	double res = (double)so / su;
	cout << "\nВаше звание: ";
	if (res < 1200.0 / 3800.0)
		cout << "Новичок";
	else if (res < 1400.0 / 3800.0)
		cout << "Ученик";
	else if (res < 1600.0 / 3800.0)
		cout << "Специалист";
	else if (res < 1900.0 / 3800.0)
		cout << "Эксперт";
	else if (res < 2200.0 / 3800.0)
		cout << "Кандидат в мастера";
	else if (res < 2300.0 / 3800.0)
		cout << "Мастер";
	else if (res < 2400.0 / 3800.0)
		cout << "Международный мастер";
	else if (res < 2600.0 / 3800.0)
		cout << "Гроссмейстер";
	else if (res < 2900.0 / 3800.0)
		cout << "Международный гроссмейстер";
	else
		cout << "Легендарный гроссмейстер";
	cout << '\n';
}

void show_proflie(string &s) {
	ifstream in("user.ota");
	set<user> users;
	string t;
	while (cin >> t) {
		string g;
		cin >> g;
		int so, su;
		cin >> so >> su;

		if (t == s) {
			cout << "Ваш логин " << s << '\n';
			cout << "Ваш пароль ";
			forn(i, 0, (int)g.size())
				cout << '*';
			cout << '\n';
			status(so, su);
			return;
		}
	}
}

void create_account(string &s) {
	cout << "Для того, чтобы программа вас смогла иденфицировать, создайте любой пароль без пробелов, включающий в себя не более 10 символов\n";
	string h;
	int durak = 0;
	while (true) {
		if (durak > 2) {
			cout << "Вы использовали 3 неудачных попыток создания пароля\nЕго сейчас сгенерирует программа\n";
			int len_pass = random() % 10 + 1;
			h = "";
			forn(i, 0, len_pass) {
				int type = random() % 3;
				if (type == 0)
					h += random() % 10 + '0';
				if (type == 1)
					h += random() % 26 + 'a';
				if (type == 2)
					h += random() % 26 + 'A';
			}
			break;
		}
		getline(cin, h);
		if (h.size() > 10) {
			cout << "Пароль должен быть составлен не более 10 символами\n";
			durak++;
			continue;
		}
		for (char c : h) {
			if (c == ' ') {
				cout << "Пароль не должен содержать пробела\n";
				durak++;
				continue;
			}
			if (!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c  <= '9')) {
				cout << "Пароль должен быть составлен латинскими буквами или цифрами\n";
				durak++;
				continue;
			}
		}
		break;
	}

	cout << "Ваш пароль: " << h << '\n';

	ofstream out("user.ota", ios::app);
	out << s << ' ' << h << " 0 0\n";
}

string userapi = "Not a user";// user was not detected
void login(int cnt) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (cnt)
		cout << "----------------------------------------------------------------------------------------------------------------------------------\n";
	cout << "Введите ваш логин (если его не будет, то создастся новый пользователь)\nПомните, что логин состоит без пробелов и до 10 символов\n";
	string s;
	int durak = 0;
	while (true) {
		if (durak > 2) {
			cout << "К сожалению, я не смог вас иденфицировать.\n";
			return;
		}
		getline(cin, s);
		for (char c : s)
			if (c == ' ') {
				cout << "Логин должен быть без пробелов\n";
				durak++;
				continue;
			}
		if (s.size() > 10) {
			cout << "Логин не может быть длиннее, чем 10 символов\n";
			durak++;
			continue;
		}
		break;
	}

	set<string> counter;
	for (auto &i : users) {
		counter.insert(i.name);
	}

	if (!counter.count(s)) {
		cout << "Такого логина не существует. Создать новый?\nВведите тогда любую цифру\n";
		cout << "Введите back для повторной попытки ввода\n";
		string n;
		getline(cin, n);
		if (n.size() == 1 && n[0] >= '0' && n[0] <= '9') {
			create_account(s);
			cout << "Аккаунт успешно создан. Программа вынуждена закрыть себя.\nВведите enter.\n";
			char c;
			scanf("%c", &c);
			exit(0);
		}
		else if (n == "back")
			login(++cnt);
		else {
			cout << "К сожалению, я не смог вас иденфицировать.\n";
			return;
		}
	}
	else {
		cout << "Введите пароль для " << s << '\n';

		auto it = users.begin();
		while (it != users.end() && it->name != s)
			it++;

		string n;
		int durak = 0;
		while (true) {
			if (durak > 2) {
				cout << "Вы сделали слишком много попыток\nВы вошли как неизвестный пользователь\n";
				return;
			}
			cin >> n;
			if (n == it->pass)
				break;
			durak++;
		}

		cout << "Вы вошли под логином " << s << '\n';
		status(it->solved, it->sum);
		cout << '\n';
		userapi = s;
	}

	return;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	setrandom();

	input(E, "europe");
	input(SA, "south-america");
	input(NA, "north-america");
	input(AF, "africa");
	input(AS, "asia");
	input(AU, "australia-and-oceania");
	get_users();

	cout << "Copyright Nikita Ota + Mr.Donaldo\n---------------------------------\n";
	cout << "Вас приветствует вторая версия программы Geography.exe, написанная на С++\n";

	//cout << "\nПредставьтесь в программе. Если вас программа ещё не знает, зарегистрируйтесь(new!)\n";
	//cout << "Введите " << char('"') << "нет" << char('"') << " без кавычек, чтобы обойти регистрацию\nИначе введите что угодно\n";
	cout << "\nХотите представиться в программе?\n";
	string qqq;
	getline(cin, qqq);
	if (qqq != "нет" && qqq != "no" && qqq != "nope" && qqq != "Нет" && qqq != "No" && qqq != "Nope" && qqq != "ytn" && qqq != "Ytn")
		login(0);

	cout << "\nВопрос:\n";
	cout << "Введите да\n";
	string mode;
	while (mode == "")
		getline(cin, mode);
	if (!(mode == "да" || mode == "yes" || mode == "lf")) {
		cout << "Включен режим дурачка\nТеперь за вас всё будет выбирать компьютер\n";
		durashka = true;
	}

	cout << "\nЗдесь есть 4 режима:\n1) Угадай столицу по названию страны (было в прошлой версии)\n2) Угадай название страны по её столице (new!)\n3) Познавательный режим. Вводится страна, выводится её столица (new!)\n";
	cout << "4) Режим составления тестов по географии на знание столиц и государств.\n";
	cout << "\nИтак, выберите режим. Введите 1 или 2, 3 или 4.\n";
	int durak = (durashka ? 47 : 0);
	if (durak == 47) {
		mode[0] = /*'0' + random() % 3 + */'1';
		cout << "За вас я выбрал режим №" << mode[0] - '0' << '\n';
	}
	else {
		while (getline(cin, mode)) {
			if (mode == "1 или 2, 3 или 4") {
				cout << "Введите не строку, а одну цифру\n";
				durak++;
				continue;
			}
			if (mode.size() > 1 || mode.size() == 1 && (mode[0] > '4' || mode[0] < '1')) {
				cout << "1 или 2, 3 или 4\n";
				durak++;
			}
			else
				break;
			if (durak > 2) {
				durak = 32;
				cout << "За вас я выбрал режим №3\n";
				break;
			}
		}
	}

	if (durak == 32)
		durak = 3;
	else
		durak = mode[0] - '0';

	cout << "------------------------------\n";
	if (durak == 1) {
		game1();
	}
	if (durak == 2) {
		game2();
	}
	if (durak == 4) {
		game4();
	}
	if (durak == 3) {
		game3();
	}

	char c;
	scanf("%c", &c);

	return 0;
}

void append_back(vector<country> &some, set<country> &lib) {
	for (auto &i : some)
		lib.insert(i);
}

void update_lib(set<country> &lib, set<int> &num) {
	for (int i : num) {
		if (i == 1)
			append_back(E, lib);
		if (i == 2)
			append_back(SA, lib);
		if (i == 3)
			append_back(NA, lib);
		if (i == 4)
			append_back(AF, lib);
		if (i == 5)
			append_back(AS, lib);
		if (i == 6)
			append_back(AU, lib);
	}
}

void game1() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "Вы перешли в режим 1.\n";
	cout << "Сначала введите количество частей света, перевод строки (enter)\n";

	string some;
	int durak = (durashka ? 47 : 0);
	if (durak == 47) {
		some += random() % 3 + 1 + '0';
		cout << "За вас выбрана цифра " << some[0] - '0' << '\n';
	}
	else {
		while (getline(cin, some)) {
			if ('1' <= some[0] && some[0] <= '6' && some.size() == 1)
				break;
			cout << "Введите цифру от 1 до 6\n";
			durak++;
			if (durak > 2) {
				cout << "За вас выбрана цифра 1\n";
				some[0] = '1';
				break;
			}
		}
	}
	if (!(durak > 2))
		cout << "Хорошо, ваша выбранная цифра " << some[0] << '\n';

	cout << "Выберите части света:\n1 - Европа\n2 - Южная Америка\n3 - Северная Америка\n4 - Африка\n5 - Азия\n6 - Австралия и Океания\n";

	int n = some[0] - '0';
	set<int> numbers;
	forn(i, 0, n) {
		durak = (durashka ? 47 : 0);
		if (durak == 47) {
			numbers.insert(i + 1);
			cout << "За вас выбрана цифра " << i + 1 << '\n';
		}
		else {
			while (getline(cin, some)) {
				if (some[0] >= '1' && some[0] <= '6' && some.size() == 1) {
					if (numbers.count(some[0] - '0'))
						cout << "Эта цифра уже введена\n";
					else
						break;
				}
				cout << "Введите цифру от 1 до 6\n";
				durak++;

				if (durak > 2) {
					cout << "За вас выбрана цифра ";
					if (numbers.empty()) {
						numbers.insert(random() % 6 + 1);
						cout << *numbers.begin() << '\n';
					}
					else {
						forn(i, 1, 7) {
							if (!numbers.count(i)) {
								cout << i << '\n';
								numbers.insert(i);
								break;
							}
						}
					}
					break;
				}// end of durak
			}
			numbers.insert(some[0] - '0');
		}
	}

	set<country> library;
	update_lib(library, numbers);

	cout << "\nВсего " << library.size() << " стран со столицами в выбранных вами частях света\n";
	cout << "Вы можете изменить количество вопросов:\n->уменьшить в 2 раза, если введете a (латинская)\n->уменьшить в 3 раза, если введете b\n->уменьшить в 4 раза, если введете с (латинская)\n->уменьшить в 5 раз, если введете d\n->поменять на введенное вами число (не большее количества стран и больше нуля!)\n";
	durak = (durashka ? 47 : 0);
	if (durak == 47) {
		;
	}
	else {
		while (getline(cin, some)) {
			if (durak > 1) {
				cout << "За вас выбрано число " << library.size() << '\n';
				break;
			}
			if (some[0] > '0' && some[0] <= '9') {
				int q = 0;
				for (auto &i : some) {
					q += i - '0';
					q *= 10;
				}
				q /= 10;
				if (q <= (int)library.size())
					break;
			}
			if (some[0] >= 'a' && some[0] <= 'd' && some.size() == 1)
				break;

			cout << "Введите латинские буквы от a до d или число, большее нуля и меньшее " << library.size() << '\n';
			durak++;
		}
	}
	n = library.size();
	if (durak > 1) {
		;
	}
	else {
		if (some[0] >= 'a' && some[0] <= 'd') {
			n /= some[0] - 'a' + 2;
		}
		else {
			int q = 0;
			for (auto &i : some) {
				q += i - '0';
				q *= 10;
			}
			n = q / 10;
		}
	}
	if (n != library.size())
		cout << "Количество вопросов изменено с " << library.size() << " на " << n << '\n';
	else
		cout << "Количесво вопросов не изменено\n";
	
	cout << "\nВопросы:\n";
	int sum = 0;
	forn(i, 0, n) {
		int curr_pos = random() % (library.size());
		auto it = library.begin();
		while (curr_pos > 0) {
			it++;
			curr_pos--;
		}

		cout << i + 1 << ") Напишите столицу государства " << it->name << '\n';
		string s;
		int k = 0;
		while (getline(cin, s)) {
			if (s == "")
				continue;
			if (s == "не знаю") {
				if (k == it->capital.size() - 2) {
					cout << "С такими подсказками можно додуматься самому\n";
					if (random() % 10 == 7) {
						cout << "Вам повезло. Я дам вам шанс написать всё-таки ответ\n";
						getline(cin, s);
					}
					break;
				}
				cout << "Подсказка: " << (k < 3 ? k : it->capital.size() - k + 2) + 1 << "-я буква в ответе " << it->capital[(k < 3 ? k : it->capital.size() - k + 2)] << '\n';
				k++;
			}
			else
				break;
		}// end of hint
		if (s == it->capital) {
			int some = random() % 3;
			if (some == 0)
				cout << "Да, так держать!\n";
			if (some == 1)
				cout << "Это правильный ответ\n";
			if (some == 2)
				cout << "Конечно да!\n";
			sum++;
		}// end of Correct Answer
		else {
			int some = random() % 3;
			if (some == 0)
				cout << "Это был неверный ответ\n";
			if (some == 1)
				cout << "Надеюсь, в следующий раз вы напишите это правильно\n";
			if (some == 2)
				cout << "Вы ошибаетесь\n";
			cout << "Правильный ответ - " << it->capital << '\n';
		}// end of Wrong Answer
		cout << '\n';
		library.erase(it);
	}// end of forn(i, 0, n)

	cout.precision(2);
	cout << fixed;
	cout << "Ваш результат: " << sum << " из " << n << '\n';
	cout << "Это примерно " << (double)sum / n * 100.0 << "%\n";

	update_user(userapi, sum, n);

	cout << "\nТест завершён. Нажмите на любую клавишу\n";
}

void game2() {// Не обновлено
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "Вы перешли в режим 2.\n";
	cout << "Сначала введите количество частей света, перевод строки (enter)\n";

	string some;
	int durak = (durashka ? 47 : 0);
	if (durak == 47) {
		some += random() % 3 + 1 + '0';
		cout << "За вас выбрана цифра " << some[0] - '0' << '\n';
	}
	else {
		while (getline(cin, some)) {
			if ('1' <= some[0] && some[0] <= '6' && some.size() == 1)
				break;
			cout << "Введите цифру от 1 до 6\n";
			durak++;
			if (durak > 2) {
				cout << "За вас выбрана цифра 1\n";
				some[0] = '1';
				break;
			}
		}
	}
	if (!(durak > 2))
		cout << "Хорошо, ваша выбранная цифра " << some[0] << '\n';

	cout << "Выберите части света:\n1 - Европа\n2 - Южная Америка\n3 - Северная Америка\n4 - Африка\n5 - Азия\n6 - Австралия и Океания\n";
	int n = some[0] - '0';
	set<int> numbers;
	forn(i, 0, n) {
		durak = (durashka ? 47 : 0);
		if (durak == 47) {
			numbers.insert(i + 1);
			cout << "За вас выбрана цифра " << i + 1 << '\n';
		}
		else {
			while (getline(cin, some)) {
				if (some[0] >= '1' && some[0] <= '6' && some.size() == 1) {
					if (numbers.count(some[0] - '0'))
						cout << "Эта цифра уже введена\n";
					else
						break;
				}
				cout << "Введите цифру от 1 до 6\n";
				durak++;

				if (durak > 2) {
					cout << "За вас выбрана цифра ";
					if (numbers.empty()) {
						numbers.insert(random() % 6 + 1);
						cout << *numbers.begin() << '\n';
					}
					else {
						forn(i, 1, 7) {
							if (!numbers.count(i)) {
								cout << i << '\n';
								numbers.insert(i);
								break;
							}
						}
					}
					break;
				}// end of durak
			}
			numbers.insert(some[0] - '0');
		}
	}

	set<country> library;
	update_lib(library, numbers);

	cout << "\nВсего " << library.size() << " стран со столицами в выбранных вами частях света\n";
	cout << "Вы можете изменить количество вопросов:\n->уменьшить в 2 раза, если введете a (латинская)\n->уменьшить в 3 раза, если введете b\n->уменьшить в 4 раза, если введете с (латинская)\n->уменьшить в 5 раз, если введете d\n->поменять на введенное вами число (не большее количества стран и больше нуля!)\n";
	durak = (durashka ? 47 : 0);
	if (durak == 47) {
		;
	}
	else {
		while (getline(cin, some)) {
			if (durak > 1) {
				cout << "За вас выбрано число " << library.size() << '\n';
				break;
			}
			if (some[0] > '0' && some[0] <= '9') {
				int q = 0;
				for (auto &i : some) {
					q += i - '0';
					q *= 10;
				}
				q /= 10;
				if (q <= (int)library.size())
					break;
			}
			if (some[0] >= 'a' && some[0] <= 'd' && some.size() == 1)
				break;

			cout << "Введите латинские буквы от a до d или число, большее нуля и меньшее " << library.size() << '\n';
			durak++;
		}
	}
	n = library.size();
	if (durak > 1) {
		;
	}
	else {
		if (some[0] >= 'a' && some[0] <= 'd') {
			n /= some[0] - 'a' + 2;
		}
		else {
			int q = 0;
			for (auto &i : some) {
				q += i - '0';
				q *= 10;
			}
			n = q / 10;
		}
	}
	if (n != library.size())
		cout << "Количество вопросов изменено с " << library.size() << " на " << n << '\n';
	else
		cout << "Количесво вопросов не изменено\n";

	cout << "\nВопросы:\n";
	int sum = 0;
	forn(i, 0, n) {
		int curr_pos = random() % (library.size());
		auto it = library.begin();
		while (curr_pos > 0) {
			it++;
			curr_pos--;
		}

		cout << i + 1 << ") Напишите название страны по столице " << it->capital << '\n';
		string s;
		int k = 0;
		while (getline(cin, s)) {
			if (s == "")
				continue;
			if (s == "не знаю") {
				if (k == it->name.size() - 2) {
					cout << "С такими подсказками можно додуматься самому\n";
					if (random() % 10 == 7) {
						cout << "Вам повезло. Я дам вам шанс написать всё-таки ответ\n";
						getline(cin, s);
					}
					break;
				}
				cout << "Подсказка: " << (k < 3 ? k : it->capital.size() - k + 2) + 1 << "-я буква в ответе " << it->capital[(k < 3 ? k : it->capital.size() - k + 2)] << '\n';
				k++;
			}
			else
				break;
		}// end of hint
		if (s == it->name) {
			int some = random() % 3;
			if (some == 0)
				cout << "Да, так держать!\n";
			if (some == 1)
				cout << "Это правильный ответ\n";
			if (some == 2)
				cout << "Конечно да!\n";
			sum++;
		}// end of Correct Answer
		else {
			int some = random() % 3;
			if (some == 0)
				cout << "Это был неверный ответ\n";
			if (some == 1)
				cout << "Надеюсь, в следующий раз вы напишите это правильно\n";
			if (some == 2)
				cout << "Вы ошибаетесь\n";
			cout << "Правильный ответ - " << it->name << '\n';
		}// end of Wrong Answer
		cout << '\n';
		library.erase(it);
	}// end of forn(i, 0, n)

	cout.precision(2);
	cout << fixed;
	cout << "Ваш результат: " << sum << " из " << n << '\n';
	cout << "Это примерно " << (double)sum / n * 100.0 << "%\n";

	update_user(userapi, sum, n);

	cout << "\nТест завершён. Нажмите на любую клавишу\n";
}

void game3() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "Добро пожаловать в познавательный режим 3\n";
	cout << "Здесь вы просто вводите некоторое слово\n";
	cout << "Программа определяет слово как столицу или название государства, или сообщает, что введенное слово не относится ни к чему\n";
	cout << "Если вы введёте название части света, то вам будет выдан список стран этой части чвета(new!)\n";
	cout << "Программа будет работать до того, как вы введете кодовое слово\n";
	cout << "-------Список кодовых слов-------\n";
	cout << "нет, не надо, все, всё, хватит, end, finish\n";

	struct query {
		string name;
		string capital;
		int type;

		bool operator < (const query &q) const {
			return name < q.name;
		}
	};

	set<query> dic;
	for (auto &i : E) {
		query curr;
		curr.name = i.name;
		curr.capital = i.capital;
		curr.type = 1;
		dic.insert(curr);
	}
	for (auto &i : SA) {
		query curr;
		curr.name = i.name;
		curr.capital = i.capital;
		curr.type = 2;
		dic.insert(curr);
	}
	for (auto &i : NA) {
		query curr;
		curr.name = i.name;
		curr.capital = i.capital;
		curr.type = 3;
		dic.insert(curr);
	}
	for (auto &i : AF) {
		query curr;
		curr.name = i.name;
		curr.capital = i.capital;
		curr.type = 4;
		dic.insert(curr);
	}
	for (auto &i : AS) {
		query curr;
		curr.name = i.name;
		curr.capital = i.capital;
		curr.type = 5;
		dic.insert(curr);
	}
	for (auto &i : AU) {
		query curr;
		curr.name = i.name;
		curr.capital = i.capital;
		curr.type = 6;
		dic.insert(curr);
	}

	cout << "------------------------------------------\n";
	string s;
	while (getline(cin, s)) {
		if (s == "нет" || s == "не надо" || s == "все" || s == "всё" || s == "хватит" || s == "end" || s == "finish")
			break;

		if (s == "Азия" || s == "Южная Америка" || s == "Северная Америка" || s == "Европа" || s == "Австралия" || s == "Австралия и океания" || s == "Австралия и Океания" || s == "Африка") {
			if (s == "Азия") {
				cout << "В Азии находятся:\n";
				for (auto &i : AS)
					cout << i.name << '\n';
			}
			if (s == "Южная Америка") {
				cout << "В Южной Америке находятся:\n";
				for (auto &i : SA)
					cout << i.name << '\n';
			}
			if (s == "Северная Америка") {
				cout << "В Северной Америке находятся:\n";
				for (auto &i : NA)
					cout << i.name << '\n';
			}
			if (s == "Европа") {
				cout << "В Европе находятся:\n";
				for (auto &i : E)
					cout << i.name << '\n';
			}
			if (s == "Австралия" || s == "Австралия и океания" || s == "Австралия и Океания") {
				cout << "В этой части света находятся:\n";
				for (auto &i : AU)
					cout << i.name << '\n';
			}
			if (s == "Африка") {
				cout << "В Африке находятся:\n";
				for (auto &i : AF)
					cout << i.name << '\n';
			}

			continue;
		}

		auto it = dic.begin();
		while (it != dic.end() && it->name != s && it->capital != s)
			it++;

		if (it == dic.end()) {
			cout << "Это не столица и не название государства\n";
			continue;
		}

		if (it->name == s) {
			cout << "Столицей государства " << s << " является " << it->capital << '\n';
		}
		else {
			cout << "Государство, столицей которого является " << s << ", - " << it->name << '\n';
		}
		cout << "Государство находится в ";
		if (it->type == 1)
			cout << "Европе\n";
		if (it->type == 2)
			cout << "Южной Америке\n";
		if (it->type == 3)
			cout << "Северной Америке\n";
		if (it->type == 4)
			cout << "Африке\n";
		if (it->type == 5)
			cout << "Азии\n";
		if (it->type == 6)
			cout << "Австралии и океании\n";
		cout << "------------------------------------------\n";
	}

	cout << "Успехов!\n";
}

int StrToInt(string &s) {
	int sum = 0;
	for (char c : s) {
		sum += c - '0';
		sum *= 10;
	}
	sum /= 10;

	return sum;
}

void game4() {
	cout << "Благодарю за выбор режима 4\n";
	cout << "Здесь можно быстро составить список заданий для нескольких вариантов\n";
	cout << "Bведите количество частей света, которое вы хотите использовать для составления теста\n";

	string some;
	int durak = (durashka ? 47 : 0);
	if (durak == 47) {
		some += random() % 3 + 1 + '0';
		cout << "За вас выбрана цифра " << some[0] - '0' << '\n';
	}
	else {
		while (getline(cin, some)) {
			if ('1' <= some[0] && some[0] <= '6' && some.size() == 1)
				break;
			cout << "Введите цифру от 1 до 6\n";
			durak++;
			if (durak > 2) {
				cout << "За вас выбрана цифра 1\n";
				some[0] = '1';
				break;
			}
		}
	}
	if (!(durak > 2))
		cout << "Хорошо, ваша выбранная цифра " << some[0] << '\n';

	cout << "Выберите части света:\n1 - Европа\n2 - Южная Америка\n3 - Северная Америка\n4 - Африка\n5 - Азия\n6 - Австралия и Океания\n";
	int n = some[0] - '0';
	set<int> numbers;
	forn(i, 0, n) {
		durak = (durashka ? 47 : 0);
		if (durak == 47) {
			numbers.insert(i + 1);
			cout << "За вас выбрана цифра " << i + 1 << '\n';
		}
		else {
			while (getline(cin, some)) {
				if (some[0] >= '1' && some[0] <= '6' && some.size() == 1) {
					if (numbers.count(some[0] - '0'))
						cout << "Эта цифра уже введена\n";
					else
						break;
				}
				cout << "Введите цифру от 1 до 6\n";
				durak++;

				if (durak > 2) {
					cout << "За вас выбрана цифра ";
					if (numbers.empty()) {
						numbers.insert(random() % 6 + 1);
						cout << *numbers.begin() << '\n';
					}
					else {
						forn(i, 1, 7) {
							if (!numbers.count(i)) {
								cout << i << '\n';
								numbers.insert(i);
								break;
							}
						}
					}
					break;
				}// end of durak
			}
			numbers.insert(some[0] - '0');
		}
	}

	set<country> library;
	update_lib(library, numbers);

	cout << "\nВсего " << library.size() << " стран со столицами в выбранных вами частях света\n";

	cout << "Теперь введите количество вариантов\n";
	durak = 0;
	int option;
	while (true) {
		if (durak > 2) {
			cout << "За вас выбрано число ";
			option = random() % library.size();
			break;
		}
		getline(cin, some);
		if (some == "") {
			continue;
		}

		bool flag = false;
		for (char c : some)
			if (!(c >= '0' && c <= '9'))
				flag = true;

		if (flag || some.size() > 10) {
			cout << "Введите число\n";
			durak++;
			continue;
		}

		option = StrToInt(some);
		if (option > (int)library.size()) {
			cout << "При вводе такого числа всем вариантам будет задано по 0 задач\n";
			durak++;
			continue;
		}

		break;
	}

	int m = library.size() / option;
	cout << "Сейчас сделаю " << option << " вариантов\n";

	cout << "Сколько заданий надо сделать для каждого варианта?\n(Максимум заданий " << m << ")\n";
	some = "";
	durak = 0;
	int sum;
	while (true) {
		if (durak > 2) {
			cout << "За вас выбрано " << m << '\n';
			sum = m;
			break;
		}

		getline(cin, some);
		if (some == "")
			continue;

		for (char c : some) {
			if (!(c >= '0' && c <= '9')) {
				cout << "Введите число\n";
				durak++;
				continue;
			}
		}

		sum = StrToInt(some);
		if (sum > m) {
			cout << "Введите число, меньшее " << m << '\n';
			durak++;
			continue;
		}
		if (sum > 30) {
			cout << "Введите число, меньшее 30 для ускорения программы\n";
			durak++;
			continue;
		}
		break;
	}

	//cout << "Для каждого варианта будет задано " << m << " задач\n";
	forn(i, 0, option) {
		cout << i + 1 << "-й вариант:\n";

		forn(j, 0, sum) {
			bool capital = random() & 1;
			int pos = random() % library.size();
			auto it = library.begin();
			while (it != library.end() && pos > 0) {
				it++;
				pos--;
			}

			cout << j + 1 << ") ";
			if (capital) {
				cout << it->name << " - ...\n";
			}
			else {
				cout << "... - " << it->capital << '\n';
			}

			library.erase(it);
		}

		cout << '\n';
	}

	cout << "Успешного проведения контрольной работы!\n";
}