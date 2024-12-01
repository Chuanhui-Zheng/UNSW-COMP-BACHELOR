// Implementation of the Set ADT using a balanced BST
// COMP2521 22T2 Assignment 1

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Set.h"
#include "SetStructs.h"

////////////////////////////////////////////////////////////////////////
// Basic Operations

/**
 * Creates a new empty set
 */
Set SetNew(void) {
	Set sss = malloc(sizeof(Set));
	sss->tree=NULL;
	return sss;
}

/**
 * Frees all memory associated with the given set
 */
void SetFree(Set s) {
	free(s);
}

/**
 * Inserts an item into the set
 */
void SetInsert(Set s, int item) {
	struct node *new = malloc(sizeof(struct node));
	new->item = item;
	new->right = NULL;
	new->left = NULL;
	struct node *a = s->tree;
	while (a != NULL){
		if (item > a->item){
			if (a->right == NULL){
				a->right = new;
				return;
			}
			else{
				a = a->right;
			}
		}
		else if (item < a->item){
			if (a->left == NULL){
				a->left = new;
				return;
			}
			else{
				a = a->left;
			}
		}
		else{
			return;
		}
	}
	s->tree = new;
}

/**
 * Returns the number of elements in the set
 */
 int find(struct node *root){
	if (root == NULL){
		return 0;
	}
	else{
		return (find(root->right)+find(root->left)+1);
	}
}

int SetSize(Set s) {
	// int m = find(s->tree);
	// printf("%d\n", m);
	return find(s->tree);
}

/**
 * Returns true if the set contains the given item, and false otherwise
 */
bool SetContains(Set s, int item) {
	struct node *b = s->tree;
	while (b != NULL){
		if (item > b->item){
			b = b->right;
		}
		else if (item < b->item){
			b = b->left;
		}
		else{
			return true;
		}
	}
	return false;
}


/**
 * Prints the given set in the format
 * {elem1, elem2, elem3}
 */
int num;

void inorder(struct node *c, int size) {
	if (c == NULL){
		return;
	}
	else{
		inorder(c->left,size);
		printf("%d",c->item);
		num++;
		if (num != size){printf(", ");}
		inorder(c->right, size);
	}
}

void SetShow(Set s){
	num = 0;
	if (SetSize(s) == 0){
		printf("{}");
	}
	else{
		printf("{");
		inorder(s->tree, SetSize(s));
		printf("}");
	}
}

////////////////////////////////////////////////////////////////////////
// Further Operations

/**
 * Returns a new set representing the union of the two sets
 */

void unifunc(Set new, struct node *n){
	if (n == NULL){
		return;
	}
	else{
		SetInsert(new, n->item);
		unifunc(new, n->right);
		unifunc(new, n->left);
	}
}

Set SetUnion(Set s1, Set s2) {
	Set unionset = SetNew();
	unifunc(unionset, s1->tree);
	unifunc(unionset, s2->tree);
	return unionset;
}


/**
 * Returns a new set representing the intersection of the two sets
 */

void interfunc(Set new, struct node *n, Set s2){
	if (n == NULL){
		return;
	}
	else{
		if (SetContains(s2, n->item)){
			SetInsert(new, n->item);
		}
	interfunc(new, n->right, s2);
	interfunc(new, n->left, s2);
	}
}

Set SetIntersection(Set s1, Set s2) {
	Set intersectionset = SetNew();
	interfunc(intersectionset, s1->tree, s2);
	return intersectionset;
}

/**
 * Returns a new set representing the set difference s1 - s2
 */

void difffunc(struct node *n, Set s2, Set diffnew){
	if (n == NULL){
		return;
	}
	else{
		if (SetContains(s2, n->item) == false){
			SetInsert(diffnew, n->item);
		}
		difffunc(n->right, s2, diffnew);
		difffunc(n->left, s2, diffnew);
	}
}

Set SetDifference(Set s1, Set s2) {
	Set setdiff = SetNew();
	difffunc(s1->tree, s2, setdiff);
	return setdiff;
}

/**
 * Returns true if the two sets are equal, and false otherwise
 */

bool s1ins2func(struct node *n, Set s2){
	if (n == NULL){
		return true;
	}
	else{
		if (SetContains(s2, n->item)){
			return (s1ins2func(n->right, s2) && s1ins2func(n->left, s2));
		}
		else{
			return false;
		}
	}
	return true;
}
 
bool SetEquals(Set s1, Set s2) {
	if (SetSize(s1) != SetSize(s2)){
		return false;
	}
	else{
		return s1ins2func(s1->tree, s2);
	}
}

/**
 * Returns true if set s1 is a subset of set s2, and false otherwise
 */

bool SetSubset(Set s1, Set s2) {
	return s1ins2func(s1->tree, s2);
}

/**
 * Finds the floor of a given item in a set
 */

int store;

void floorfunc(struct node *n, int item){
	if (n == NULL){
		return;
	}
	else{
		if (item >= n->item){
			if (n->item > store){
				store = n->item;
			}
		}
		floorfunc(n->right, item);
		floorfunc(n->left, item);
	}
}

int SetFloor(Set s, int item) {
	store = -599;
	floorfunc(s->tree, item);
	if (store == -599){
		return UNDEFINED;
	}
	else{
		return store;
	}
}

/** 
 * Returns the ceiling of a given item in a set
 */

void ceilfunc(struct node *n, int item){
	if (n == NULL){
		return;
	}
	else{
		if (item <= n->item){
			if (n->item < store){
				store = n->item;
			}
		}
		ceilfunc(n->right, item);
		ceilfunc(n->left, item);
	}
}

int SetCeiling(Set s, int item) {
	store = 599;
	ceilfunc(s->tree, item);
	if (store == 599){
		return UNDEFINED;
	}
	else{
		return store;
	}
}

////////////////////////////////////////////////////////////////////////
// Cursor Operations

/**
 * Creates a new cursor positioned at the smallest element of the set
 */
SetCursor SetCursorNew(Set s) {
	
	return NULL;
}

/**
 * Frees all memory associated with the given cursor
 */
void SetCursorFree(SetCursor cur) {
	// TODO
}

/**
 * Returns the element at the cursor's current position, and then moves
 * the cursor to the next greatest element. If there is no next greatest
 * element, then all subsequent calls to SetCursorNext on this cursor
 * should return UNDEFINED.
 */
int SetCursorNext(SetCursor cur) {
	// TODO
	return UNDEFINED;
}

////////////////////////////////////////////////////////////////////////

