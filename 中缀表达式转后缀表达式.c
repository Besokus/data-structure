#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXSIZE 50

typedef struct {
	char* data;
	int top;
}sstack;

sstack s1, s2;//结果栈,符号栈.


sstack initstack() {
	//指针模拟开数组
	sstack s;
	s.data = (char*)malloc(sizeof(char)*MAXSIZE);
	if (s.data == NULL) {
		printf("初始化失败");
		return;
	}
	s.top = -1;//指向实际栈顶位置
	return s;
}

//判断优先级
int judge_(char m) {
	if (m == '^') return 3;
	if (m == '*' || m == '/') return 2;
	if (m == '+' || m == '-') return 1;
	if (m == '(') return 0;
	return -1;
}
//返回符号优先级,在符号栈入栈时判断
int judge_symbol(char n,char m) {
	return judge_(n) - judge_(m);
}

//压入栈
void push_1(sstack* s, char m) {
	s->top++;
	s->data[s->top] = m;
}

//符号入栈
void push_2(sstack* s, char m) {
	if (s->top == -1) {
		s->top++;
		s->data[s->top] = m;
		return;
	}
	else {
		//int top_ = s->top - 1;//top前一个
		if (m == '(') {
			s->top++;
			s->data[s->top] = m;
			return;
		}
		else if (m == ')') {
			//s2的top数据
			while (s->data[s->top] != '(') {
				push_1(&s1, s->data[s->top]);
				s->top--;
			}
			//出栈')'
			s->top--;
			return;
		}
		else {
			//特殊"^"
			if (judge_(m) == judge_(s->data[s->top]) && m == '^') {
				s->top++;
				s->data[s->top] = m;
				return;
			}
			//判断优先级
			while (s->top != -1 && judge_(m) <= judge_(s->data[s->top])) {
				push_1(&s1, s->data[s->top]);
				s->top--;
			}
			s->top++;
			s->data[s->top] = m;
			
		}
	}
}

//判断符号数字
void judge(char m) {
	if (m >= 48 && m <= 57) {
		//进s1栈
		push_1(&s1, m);
		return;
	}
	//符号
	if (m >= 40 && m <= 47 && m != 46 && m != 44||m=='^') {
		push_2(&s2, m);
		return;
	}
}

int main() {
	s1 = initstack();
	s2 = initstack();
	char m;
	while ((m = getchar()) != '\n') {
		judge(m);
	}
	//输入完将s2全部入s1
	while (s2.top != -1) {
		push_1(&s1, s2.data[s2.top]);
		s2.top--;
	}
	for (int i = 0; i <= s1.top; i++) {
		printf("%c ", s1.data[i]);
	}
	return 0;
}
