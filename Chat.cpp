#include <string>
#include "Chat.h"
#include "HashTable.h"
#include "SHA1.h"

Chat::Chat()
{
	_data = new HashTable();
}

Chat::~Chat()
{
	delete _data;
}

void Chat::reg(const char _login[LOGINLENGTH], const char _pass[], const int pass_length) {
	// Ваш код
	const uint* hash = sha1(_pass, pass_length);

	_data->add(_login, hash);
	delete[] hash;
}
bool Chat::login(const char _login[LOGINLENGTH], const char _pass[], const int pass_length) {
	// Ваш код
	// Нужно вернуть true в случае успешного логина
	const uint* saved = _data->find(_login);
	if (saved)
	{
		const uint* current = sha1(_pass, pass_length);
		bool logged = !memcmp(saved, current, SHA1HASHLENGTHBYTES);
		delete[]current;
		return logged;
	}
	return false;
}
