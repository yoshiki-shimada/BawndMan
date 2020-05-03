/*******************************************************************
* @file		RemTask.h
* @brief	タスクシステム.h
* @author	yshimada
* @data		20191215
*******************************************************************/

#pragma once
//-------------------------------------------------------------
//! class
class CRemTask;
class CRemTaskList;
class CRemTaskIter;

//=============================================================
// class RemTask
//=============================================================
class CRemTask {
	friend CRemTaskList;
	friend CRemTaskIter;

	// タスクリストへのポインタ
	CRemTaskList* TaskList;

	// 前後のタスクへのポインタ
	CRemTask* Prev, * Next;

	// タスクリストを指定しないnew, deleteを無効にする
	void* operator new(size_t t) {}
	void operator delete(void* p) {}

protected:
	// new, deleteの処理：
	// 適切なnew, delete演算子をサブクラスで定義する
	static void* operator_new(size_t t, CRemTaskList* task_list);
	static void operator_delete(void* p, CRemTaskList* task_list);

public:
	CRemTask(CRemTaskList* task_list);
	virtual ~CRemTask();
};

//=============================================================
// class RemTaskList
//=============================================================
class CRemTaskList {
	friend CRemTask;
	friend CRemTaskIter;

	// アクティブタスクリスト、フリータスクリスト
	CRemTask* ActiveTask, * FreeTask;

	// タスクの最大サイズ、タスクの最大数、フリータスクの数
	int MaxTaskSize, MaxNumTask, NumFreeTask;

public:
	// コンストラクタ
	CRemTaskList(int max_task_size, int max_num_task);

	// タスクの数
	int GetNumFreeTask() { return NumFreeTask; }
	int GetNumActiveTask() { return (MaxNumTask - NumFreeTask); }

	// 全タスクの消去
	void DeleteTask();
};

//=============================================================
// class RemTaskIter
//=============================================================
class CRemTaskIter {

protected:
	CRemTaskList* TaskList;
	CRemTask* Task;

public:
	// コンストラクタ
	inline CRemTaskIter(CRemTaskList* task_list)
		: TaskList(task_list), Task(task_list->ActiveTask)
	{}

	// 次の要素があるときtrue
	inline bool HasNext() {
		return (Task->Next != TaskList->ActiveTask);
	}

	// 次の要素を返す
	inline CRemTask* Next() {
		return (Task = Task->Next);
	}

	// 直前に返した要素を削除する
	inline void Remove() {
		Task = Task->Prev;
		delete Task->Next;
	}
};