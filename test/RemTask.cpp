/*******************************************************************
* @file		RemTask.cpp
* @brief	タスクシステム.cpp
* @author	yshimada
* @data		20191215
*******************************************************************/

#include "RemTask.h"
#include <stdio.h>
#include <assert.h>

/*****************************************
* @brief	タスクの生成、newの処理をする
* @param	[in]	t タスクサイズ	Task_list タスクリスト名
* @return	タスクの状態を返す
*****************************************/
void* CRemTask::operator_new(size_t t, CRemTaskList* task_list) {

	// クラスサイズが最大サイズを超えたらエラー
	assert(t <= (size_t)task_list->MaxTaskSize);

	// フリータスクがないときはNULLを返す
	if (task_list->NumFreeTask <= 0) return NULL;

	// フリータスクを1個取り出す
	CRemTask* task = task_list->FreeTask->Next;
	task_list->FreeTask->Next = task->Next;
	task_list->NumFreeTask--;

	// コンストラクタへ
	return task;
}

/*****************************************
* @brief	タスクコンストラクタ
*****************************************/
CRemTask::CRemTask(CRemTaskList* task_list)
	: TaskList(task_list)
{
	// タスクをアクティブタスクリストに挿入する
	Prev = task_list->ActiveTask->Prev;
	Next = task_list->ActiveTask;
	Prev->Next = Next->Prev = this;
}

/*****************************************
* @brief	デストラクタ
*****************************************/
CRemTask::~CRemTask() {
	// タスクをアクティブタスクリストから削除する
	Prev->Next = Next;
	Next->Prev = Prev;
}

/*****************************************
* @brief	デリート処理
*****************************************/
void CRemTask::operator_delete(void* p, CRemTaskList* task_list) {
	// タスク
	CRemTask* task = (CRemTask*)p;

	// タスクをフリータスクリストに挿入する
	task->Next = task_list->FreeTask->Next;
	task_list->FreeTask->Next = task;
	task_list->NumFreeTask++;

	// フリータスク数が最大タスク数を超えたらエラー
	// （deleteの重複呼び出しなど）
	assert(task_list->NumFreeTask <= task_list->MaxNumTask);
}

/*****************************************
* @brief	初期化
*****************************************/
CRemTaskList::CRemTaskList(int max_size, int max_num)
	: MaxTaskSize(max_size), MaxNumTask(max_num), NumFreeTask(max_num)
{
	// タスク初期化用のマクロ
	#define TASK(INDEX)		((CRemTask*)(buf + max_size * (INDEX)))

	// タスク用メモリの確保
	char* buf = new char[max_size * (max_num + 2)];

	// アクティブタスクリストの初期化
	ActiveTask = TASK(0);
	ActiveTask->Prev = ActiveTask->Next = ActiveTask;

	// フリータスクリストの初期化
	FreeTask = TASK(1);
	for (int i = 1; i < max_num + 1; i++) {
		TASK(i)->Next = TASK(i + 1);
	}
	TASK(max_num + 1)->Next = FreeTask;
}

/*****************************************
* @brief	全タスクの削除
*****************************************/
void CRemTaskList::DeleteTask() {
	for (CRemTaskIter i(this); i.HasNext(); i.Next(), i.Remove());
}