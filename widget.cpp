#include "widget.h"
#include "ui_widget.h"
#include <QStack>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    //设置UI美化效果
    ui->setupUi(this);
    QFont font("微软雅黑", 20);
    ui->lineEdit->setFont(font);

    this->setWindowTitle("普通简单计算器");
    this->setStyleSheet(
        // 窗口背景
        "QWidget {"
        "    background-color: #e8edeeff;"
        "}"
        // 普通按钮样式
        "QPushButton {"
        "    font-size: 24px;"
        "    font-color: #2c3e50;"
        "    background-color: #5aa0a5ff;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 4px;"
        "    padding: 6px 12px;"
        "}"
        // 鼠标悬停按钮样式
        "QPushButton:hover {"
        "    background-color: #5ac4c9;"
        "    color: white;"
        "}"
        // 输入框样式
        "QLineEdit {"
        "    background-color: #677d92ff;"
        "    color: #ecf0f1;"
        "    font-size: 24px;"
        "    border-radius: 10px;"
        "    border: 2px solid #60768dff;"
        "    padding-right: 15px;"
        "    text-align: right;"
        "}"
        
    );
}


Widget::~Widget()
{
    delete ui;
}

void Widget::on_pbt1_clicked()
{
    expression += "1";
    ui->lineEdit->setText(expression);
}
void Widget::on_pbt2_clicked()
{
    expression += "2";
    ui->lineEdit->setText(expression);
}
void Widget::on_pbt3_clicked()
{
    expression += "3";
    ui->lineEdit->setText(expression);
}
void Widget::on_pbt4_clicked()
{
    expression += "4";
    ui->lineEdit->setText(expression);
}
void Widget::on_pbt5_clicked()
{
    expression += "5";
    ui->lineEdit->setText(expression);
}
void Widget::on_pbt6_clicked()
{
    expression += "6";
    ui->lineEdit->setText(expression);
}
void Widget::on_pbt7_clicked()
{
    expression += "7";
    ui->lineEdit->setText(expression);
}
void Widget::on_pbt8_clicked()
{
    expression += "8";
    ui->lineEdit->setText(expression);
}
void Widget::on_pbt9_clicked()
{
    expression += "9";
    ui->lineEdit->setText(expression);
}
void Widget::on_pbt0_clicked()
{
    expression += "0";
    ui->lineEdit->setText(expression);
}
void Widget::on_Jiajian_jia_clicked(){
    expression += "+";
    ui->lineEdit->setText(expression);
}
void Widget::on_Jiajian_jian_clicked(){
    expression += "-";
    ui->lineEdit->setText(expression);
}
void Widget::on_chengfa_clicked(){
    expression += "*";
    ui->lineEdit->setText(expression);
}
void Widget::on_chufa_clicked(){
    expression += "/";
    ui->lineEdit->setText(expression);
}
void Widget::on_Kuohao_left_clicked(){
    expression += "(";
    ui->lineEdit->setText(expression);
}
void Widget::on_Kuohao_right_clicked(){
    expression += ")";
    ui->lineEdit->setText(expression);
}
void Widget::on_Clear_clicked(){
    expression.clear();
    ui->lineEdit->setText(expression);
}
void Widget::on_Del_clicked(){
    if(!expression.isEmpty()){
        expression.chop(1);
        ui->lineEdit->setText(expression);
    }
}

// 计算结果等号
void Widget::on_dengyuhao_clicked()
{
    // 简单的表达式计算实现
    // 注意：这是一个简化版本，仅支持基本的四则运算和括号
    
    auto calculate = [](double a, double b, char op) -> double {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
            default: return 0;
        }
    };
    
    QStack<double> numStack;      // 数字栈 - 改为double类型
    QStack<char> opStack;         // 运算符栈
    
    // 将QString转换为QByteArray，然后转换为char*
    QByteArray ba = expression.toLatin1();
    const char* str = ba.data();
    int i = 0;
    
    while (str[i] != '\0') {
        if (str[i] == ' ') {
            // 跳过空格
            i++;
            continue;
        }
        else if (str[i] == '(') {
            // 左括号直接入栈
            opStack.push(str[i]);
            i++;
        }
        else if (str[i] == ')') {
            // 右括号，计算直到遇到左括号
            while (!opStack.isEmpty() && opStack.top() != '(') {
                char op = opStack.pop();
                double b = numStack.pop();
                double a = numStack.pop();
                double result = calculate(a, b, op);
                numStack.push(result);
            }
            // 弹出左括号
            if (!opStack.isEmpty()) {
                opStack.pop();
            }
            i++;
        }
        else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
            // 运算符，处理优先级
            while (!opStack.isEmpty() && 
                   ((opStack.top() == '*' || opStack.top() == '/') ||
                    ((opStack.top() == '+' || opStack.top() == '-') && 
                     (str[i] == '+' || str[i] == '-')))) {
                char op = opStack.pop();
                double b = numStack.pop();
                double a = numStack.pop();
                double result = calculate(a, b, op);
                numStack.push(result);
            }
            opStack.push(str[i]);
            i++;
        }
        else if (str[i] >= '0' && str[i] <= '9' || str[i] == '.') {
            // 数字，处理多位数字和小数
            bool isDecimal = false;
            double num = 0.0;
            double decimalFactor = 0.1;
            
            while (str[i] >= '0' && str[i] <= '9' || str[i] == '.') {
                if (str[i] == '.') {
                    isDecimal = true;
                }
                else if (isDecimal) {
                    num += (str[i] - '0') * decimalFactor;
                    decimalFactor *= 0.1;
                }
                else {
                    num = num * 10 + (str[i] - '0');
                }
                i++;
            }
            numStack.push(num);
        }
        else {
            // 非法字符，跳过
            i++;
        }
    }
    
    // 处理剩余的运算符
    while (!opStack.isEmpty()) {
        char op = opStack.pop();
        double b = numStack.pop();
        double a = numStack.pop();
        double result = calculate(a, b, op);
        numStack.push(result);
    }
    
    // 显示结果，确保至少两位小数
    if (!numStack.isEmpty()) {
        double finalResult = numStack.pop();
        QString resultStr = QString::number(finalResult, 'f', 10); // 先保留10位小数
        // 移除末尾多余的0，但至少保留两位
        int dotPos = resultStr.indexOf('.');
        if (dotPos != -1) {
            int endPos = resultStr.length() - 1;
            while (endPos > dotPos + 2 && resultStr.at(endPos) == '0') {
                endPos--;
            }
            resultStr = resultStr.left(endPos + 1);
        }
        ui->lineEdit->setText(resultStr);
        expression = resultStr;  // 保存结果以便继续计算
    }
}