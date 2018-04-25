//
//  PostfixConverter.cpp
//  Lab2_InfixToPostfix
//
//  Created by Monica Amezquita on 3/26/18.
//  Copyright © 2018 Monica Amezquita. All rights reserved.
//

#include "PostfixConverter.hpp"
#include "ArrayStack.hpp"
#include <iostream>
#include <string>

using namespace std;

bool balancedParentheses(string str){
    
    ArrayStack<char> stack;
    
    for(int i = 0; i < str.length(); i++){
        if(str[i] == '(')
            stack.push(str[i]);
        else if(str[i] == ')'){
            if(stack.isEmpty())
                return false;
            else
                stack.pop();
        }
    }
    
    if(!stack.isEmpty())
        return false;
    else
        return true;
}

bool isOperator(char c){

    if(c == '+' || c=='-' || c=='*' || c=='/')
        return true;
    else
        return false;
}

bool balancedCharacters(string str){
    ArrayStack<char> stack;
    bool balancedSoFar;
    if(isOperator(str[0])){
        return false;
    }
    else
        stack.push(str[0]);
    
    char charToCheck;
    char prevChar;
    for(int i = 1; i < str.length(); i++){
        charToCheck = str[i];
        prevChar = str[i-1];
        
        if(isalpha(prevChar)) {
            balancedSoFar = ispunct(charToCheck);
            if(!balancedSoFar)
                return false;
        }
        
        if(ispunct(prevChar)){
            balancedSoFar = (isOperator(charToCheck)||isalpha(charToCheck));
            if(!balancedSoFar)
                return false;
        }
    }
    
    if(isOperator(str[str.length()-1])){
        return false;
    }
    else
        return true;
}

int precedence(char val){

    if(val == '+' || val == '-')
        return 0;
    else
        return 1;

}

string infixToPostfix(string str){
    ArrayStack<char> stack;
    string postfix;
    bool validParentheses = balancedParentheses(str);
    bool validChars = balancedCharacters(str);
    if(!validParentheses)
        return "Invalid Parentheses. Expression not viable for conversion to postfix.\n";
    
    else if (!validChars){
        return "Invalid string. Expression not viable for conversion to postfix.\n";
    }
    else {
        
        for(int i = 0; i < str.length(); i++){
            
            if(isalpha(str[i])){
                postfix += str[i];
            } else if(str[i] == '('){
                stack.push(str[i]);
            } else if (isOperator(str[i])){
                while(!stack.isEmpty() && (stack.peek() != '(') && (precedence(str[i]) <= precedence(stack.peek()))){
                    postfix += stack.peek();
                    stack.pop();
                }
                stack.push(str[i]);
            } else {
            
                while(stack.peek() != '('){
                
                    postfix += stack.peek();
                    stack.pop();
                }
                stack.pop();
            }
                
            
                
                    
            
            }
        while(!stack.isEmpty()){
        
            postfix += stack.peek();
            stack.pop();
        
        }
        return postfix;
        }
}

