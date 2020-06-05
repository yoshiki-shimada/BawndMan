#include "LoadScript.h"

// �G�̎�ށi���O�j
const static char* ENEMY_NAME[] = {
	"ZEnemy01"
};

/*
* @brief
*/
const static NEW_ENEMY_FUNC ENEMY_FUNC[] = {
	CZakoEnemy1::New
};

const static NEW_PORTAL_FUNC PORTAL_FUNC = {
	CSpownPortal::New
};

//-------------------------------------------------------------
int Find(string s, string pattern) {
	for (int i = 0, n = s.length(), pl = pattern.length(); i < n; i++) {
		if (s.compare(i, pl, pattern) == 0) return i;
		// �}���`�o�C�g�������ǂ������`�F�b�N
		if (isleadbyte(s[i])) i++;
	}
	// ������Ȃ��Ƃ��̃|�W�V����(Non position)
	return string::npos;
}

//-------------------------------------------------------------
string GetToken(string s, int index, string separator) {
	int sl = separator.length();
	for (int i = 0; i < index; i++) {
		int pos = Find(s, separator);
		if (pos == string::npos) return "";
		// �w�肳�ꂽ�ʒu����w�肳�ꂽ�����܂ł̕�������擾����
		s = s.substr(pos + sl);
	}

	return s.substr(0, Find(s, separator));
}

//=============================================================
CLoadScript::CLoadScript(string file)
	: nCommandIndex(0)
{
	int nFileHandle;
	char String[256] = "";

	bool comment = false;

	// �t�@�C�����J��
	nFileHandle = FileRead_open(file.c_str());

	// �t�@�C���̏I�[������܂ŕ\������
	while (FileRead_eof(nFileHandle) == 0)
	{
		// ��s�ǂݍ���
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
					Command.push_back(new CEnemyCommand(ENEMY_FUNC[i], stof(param1), stof(param2)));
				}
			}
		}
		else if (command == "portal") {
			Command.push_back(new CPortalCommand(PORTAL_FUNC, stof(param1), stof(param2), stof(param3)));
		}
	}
}

void CLoadScript::Init() {
	nCommandIndex = 0;
}

//-------------------------------------------------------------
void CLoadScript::Run() {
	while (nCommandIndex < (int)Command.size()) {
		Command[nCommandIndex]->Run();
		nCommandIndex++;
	}
}