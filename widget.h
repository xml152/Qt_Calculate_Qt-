#pragma once

#include <QWidget>
#include <string.h>
#include <QStack>

QT_BEGIN_NAMESPACE
namespace Ui {
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pbt0_clicked();
    void on_pbt1_clicked();
    void on_pbt2_clicked();
    void on_pbt3_clicked();
    void on_pbt4_clicked();
    void on_pbt5_clicked();
    void on_pbt6_clicked();
    void on_pbt7_clicked();
    void on_pbt8_clicked();
    void on_pbt9_clicked();

    void on_Jiajian_jia_clicked();
    void on_Jiajian_jian_clicked();
    void on_chengfa_clicked();
    void on_chufa_clicked();

    void on_Kuohao_right_clicked();
    void on_Kuohao_left_clicked();

    void on_Clear_clicked();
    void on_Del_clicked();

    void on_dengyuhao_clicked();

    private:
    Ui::Widget *ui;
    QString expression;
};
