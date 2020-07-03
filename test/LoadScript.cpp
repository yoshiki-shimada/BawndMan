/*******************************************************************
* @file		LloadScript.cpp
* @brief	マップ生成用.cpp
* @author	yshimada
* @data		20200109
*******************************************************************/

#include "LoadScript.h"

/**
* @brief 敵の種類、名前
*/
const static char* ENEMY_NAME[] = {
	"ZEnemy01","ZEnemy02","ZEnemy03","ZEnemy04"
};
//const static char* ENEMY_NAME02[] = {
//	"ZEnemy02"
//};
//const static char* ENEMY_NAME03[] = {
//	"ZEnemy03"
//};
//const static char* ENEMY_NAME04[] = {
//	"ZEnemy04"
//};

//const static char* PORTAL_NAME = {
//   "NPortal"/*,"RPortal"*/
//};

/**
* @brief new関数
*/
const static NEW_ENEMY_FUNC01 ENEMY_FUNC01 = {
	CZakoEnemy1::New
};
const static NEW_ENEMY_FUNC02 ENEMY_FUNC02 = {
	CZakoEnemy2::New
};
const static NEW_ENEMY_FUNC03 ENEMY_FUNC03 = {
	CZakoEnemy3::New
};
const static NEW_ENEMY_FUNC04 ENEMY_FUNC04 = {
	CZakoEnemy4::New
};

const static NEW_PORTAL_FUNC PORTAL_FUNC = {
	CSpownPortal::New
};

const static NEW_BUMPER_FUNC BUMPER_FUNC = {
	CSpownBumper::New
};

/*
* @brief	文字のポジションをチェック
* @param	[in]	s chara型配列	pattern 空白かどうか
* @return	空白のポジションを返す	見つからないときはNon position
*/
int Find(string s, string pattern) {
	for (int i = 0, n = s.length(), pl = pattern.length(); i < n; i++) {
		if (s.compare(i, pl, pattern) == 0) return i;
		// マルチバイト文字かどうかをチェック
		if (isleadbyte(s[i])) i++;
	}
	// 見つからないときのポジション(Non position)
	return string::npos;
}

/*
* @brief	指定位置からの文字列取得
* @param	[in]	s chara型配列	index いくつ目の文字列か	separator 空白かどうか
* @return	文字列を返す
*/
string GetToken(string s, int index, string separator) {
	int sl = separator.length();
	for (int i = 0; i < index; i++) {
		int pos = Find(s, separator);
		if (pos == string::npos) return "";
		// 指定された位置から指定された長さまでの文字列を取得する
		s = s.substr(pos + sl);
	}

	return s.substr(0, Find(s, separator));
}

/*
* @brief	Scriptのロード
* @param	[in]	file Scriptファイル
*/
CLoadScript::CLoadScript(string file)
	: nCommandIndex(0)
{
	int nFileHandle;
	char String[256] = "";

	bool comment = false;

	// ファイルを開く
	nFileHandle = FileRead_open(file.c_str());

	// ファイルの終端が来るまで表示する
	while (FileRead_eof(nFileHandle) == 0)
	{
		// 一行読み込み
		FileRead_gets(String, 256, nFileHandle);

		string command = GetToken(String, 0, " "),
			param0 = GetToken(String, 1, " "),
			param1 = GetToken(String, 2, " "),
			param2 = GetToken(String, 3, " "),
			param3 = GetToken(String, 4, " ");

		if (command == "*/") comment = false;
		else if (command == "/*") comment = true;

		if (comment) continue;

		if (command == "enemy") {
			for (int i = 0, in = sizeof(ENEMY_NAME) / sizeof(char*); i < in; i++) {
				if (param0 == ENEMY_NAME[i]) {
					switch (i)
					{
					case 0:
						Command.push_back(new CEnemyCommand01(ENEMY_FUNC01, stof(param1), stof(param2)));
						break;
					case 1:
						Command.push_back(new CEnemyCommand02(ENEMY_FUNC02, stof(param1), stof(param2)));
						break;
					case 2:
						Command.push_back(new CEnemyCommand03(ENEMY_FUNC03, stof(param1), stof(param2)));
						break;
					case 3:
						Command.push_back(new CEnemyCommand04(ENEMY_FUNC04, stof(param1), stof(param2)));
						break;
					}
					//Command.push_back(new CEnemyCommand01(ENEMY_FUNC01, stof(param1), stof(param2)));
				}
			}
			/*for (int i = 0, in = sizeof(ENEMY_NAME02) / sizeof(char*); i < in; i++) {
				if (param0 == ENEMY_NAME02[i]) {
					Command.push_back(new CEnemyCommand02(ENEMY_FUNC02, stof(param1), stof(param2)));
				}
			}
			for (int i = 0, in = sizeof(ENEMY_NAME03) / sizeof(char*); i < in; i++) {
				if (param0 == ENEMY_NAME03[i]) {
					Command.push_back(new CEnemyCommand03(ENEMY_FUNC03, stof(param1), stof(param2)));
				}
			}
			for (int i = 0, in = sizeof(ENEMY_NAME04) / sizeof(char*); i < in; i++) {
				if (param0 == ENEMY_NAME04[i]) {
					Command.push_back(new CEnemyCommand04(ENEMY_FUNC04, stof(param1), stof(param2)));
				}
			}*/
		}
		else if (command == "portal") {
			Command.push_back(new CPortalCommand(PORTAL_FUNC, stof(param0), stof(param1), stof(param2)));
		}
		/*else if (command == "bumper") {
			Command.push_back(new CBumperCommand(BUMPER_FUNC, stof(param0), stof(param1), stof(param2)));
		}*/
	}
}

/*
* @brief	実行開始
*/
void CLoadScript::Init() {
	nCommandIndex = 0;
}

/*
* @brief	実行設定
*/
void CLoadScript::Run() {
	while (nCommandIndex < (int)Command.size()) {
		Command[nCommandIndex]->Run();
		nCommandIndex++;
	}
}