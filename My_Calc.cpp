#include <iostream>
#include <stack>
using namespace std;


bool evalute(const char* expression, int& result);
bool calculate_expression(int operand1, int operand2, char operator1, int& result);

int main()
{
    char* exp = new char[51];
    char ch;
    int result1;
    bool repeat_flag = true;
    

    std::cout << "***********************************************\n";

    while (repeat_flag)
    { 
        std::cout << "***********Please Enter Your Expression********\n";
        std::cin.get(exp, 50);
        if (!evalute(exp, result1))
           std::cout << "\n         The Result Is = " << result1 << "\n";
        std::cout << "***********************************************\n";
        std::cout << "Do you want to continue? Press Y to continue or any key to exit\n";
        std::cin >> ch;
        if (ch != 'Y' && ch !='y')
            repeat_flag = false;
       
        cin.clear();
        std::cin.ignore(50, '\n');
        
       
    }
    delete[] exp;
    return 0;
}
// Parsing is the major part of the evalute function that distinguishes operands from operators
bool evalute(const char* expression, int& result)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int nested_exp = 0;
    int operand0 = 0;
    int operand1 = 0;
    int operand2 = 0;
    char operator1;
    bool priority_flag = false;
    int calc_result = 0;
    stack <int>  stack_operand;
    stack <char> stack_operator;
    
    while (expression[i] != '\0')//This counter increments when parsing a “(“  and decrements when a “)” is parsed
    {
        if (expression[i] == '(')
            nested_exp++; 
        else if (expression[i] == ')')
            nested_exp--;
       
        if(nested_exp < 0) // Unusual usage of bracket or unbalanced number of bracket
        {
            std::cout << "Incorrect Usage of Bracket or Unbalanced Number of Bracket Error!\n";
            return 1;
        }
        // checking the first character
        if (expression[0] == '+' || expression[0] == '-' || expression[0] == '*' || expression[0] == '/')
        {
            std::cout << "First Character Should Be A Digit Or '(' Error!\n";
            return 1;
        }
        i++;
    }
    if (nested_exp != 0)
    {
        std::cout << "Unbalanced Bracket Error!\n";
        return 1;
    }
    j = i-1; // size of expression
    while (j >= 0 )
    {
        if (expression[j] == ')')
        {
            stack_operator.push(expression[j]);
            priority_flag = false;
            j--;
        }
        else if ( expression[j] == 32) //Space detection
            j--;
        else if (expression[j] > 47 && expression[j] < 58)     //Operand recognition
        {
           // the corresponding ASCII code falls between 48 to 57
            operand0 = (int)(pow(10, k) * (expression[j] - 48) + operand0);
            k++; // k represents the number of digits in integer number
            if (!j)
            {
                stack_operand.push(operand0);
                operand0 = 0;
                k = 0;
            }
            
            j--;
        }
        //Operations recognition 
        else if (expression[j] == '+' || expression[j] == '-' || expression[j] == '*' || expression[j] == '/')
        {// check priority
            if ( priority_flag && (expression[j] == '+' || expression[j] == '-') )
            {
                if (k > 0) // means that we have a operand that has been not pushed yet
                {
                    operand1 = operand0;
                    operand0 = 0;
                    k = 0;
                }
                //pop two operands and one operatore from stacks
                operand2 = stack_operand.top();
                stack_operand.pop();
                operator1 = stack_operator.top();
                stack_operator.pop();
                if (calculate_expression(operand1, operand2, operator1, calc_result))
                    return 1;
                stack_operand.push(calc_result);
                priority_flag = false;// priority operation has been done
            }


            else if (k > 0) // means that we have a operand that has been not pushed yet
            {
                stack_operand.push(operand0);
                operand0 = 0;
                k = 0;
            }
            stack_operator.push(expression[j]);

            if (expression[j] == '*' || expression[j] == '/')
                priority_flag = true;
            j--;
        }
        else if (expression[j] == '(' )
        {
            if(!stack_operator.empty())
            {
                if (k > 0)
                {
                    stack_operand.push(operand0);// means that we have a operand that has been not pushed yet
                    operand0 = 0;
                    k = 0;
                }
                operator1 = stack_operator.top();
                while (operator1 != ')')
                {
                    operand1 = stack_operand.top();
                    stack_operand.pop();
                    operand2 = stack_operand.top();
                    stack_operand.pop();
                    operator1 = stack_operator.top();
                    stack_operator.pop();
                    if (calculate_expression(operand1, operand2, operator1, calc_result))
                        return 1;
                    stack_operand.push(calc_result);
                    operator1 = stack_operator.top();
                }
                stack_operator.pop();

                priority_flag = false;
            }
            j--;
        }
        else
        {
            std::cout << "UnExpected Character Error!\n";
            return 1;
        }
    }// parssing is finished 
    
    while (!stack_operator.empty()) //check final condition to reach the result
     //just execute operation on remaing datas in two stack
    {
        //pop two operands and one operatore from stacks each time
        operand1 = stack_operand.top();
        stack_operand.pop();
        operand2 = stack_operand.top();
        stack_operand.pop();
        operator1 = stack_operator.top();
        stack_operator.pop();
        if (calculate_expression(operand1, operand2, operator1, calc_result))
            return 1;
        stack_operand.push(calc_result);
    }
    result = stack_operand.top();
    stack_operand.pop();
    return 0;
}

/*
This function gets two operands and one operator and returns the result
*/
bool calculate_expression(int operand1, int operand2, char operator1, int& result)
{

    switch (operator1)
    {

    case '+':
        result = operand1 + operand2;
        
        break;
    case '-':
        result = operand1 - operand2;
        break;
    case '*':
        result = operand1 * operand2;
        break;
    case '/':
        if(operand2 != 0)
            result = operand1 / operand2;
        else
        {
            std::cout << "Division By Zero!\n";
            return 1;
        }
        break;
    default:
        break;
    }
    return 0;
}

