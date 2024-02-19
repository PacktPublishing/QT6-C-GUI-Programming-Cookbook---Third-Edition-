#include <QCoreApplication>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QDebug>

void filterAge()
{
    qDebug() << "== Employees above 40 year old =============";

    QSqlQuery query;
    if (query.exec("SELECT emp_name, emp_age FROM employee WHERE emp_age > 40"))
    {
        while (query.next())
        {
            qDebug() << query.value(0).toString() << query.value(1).toString();
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }
}

void getDepartmentAndBranch()
{
    qDebug() << "== Get employees' department and branch =============";

    QSqlQuery query;
    if (query.exec("SELECT emp_name, dep_name, brh_name FROM (SELECT emp_name, emp_departmentID FROM employee) AS myEmployee INNER JOIN department ON department.dep_id = myEmployee.emp_departmentID INNER JOIN branch ON branch.brh_id = department.dep_branchID"))
    {
        while (query.next())
        {
            qDebug() << query.value(0).toString() << query.value(1).toString() << query.value(2).toString();
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }
}

void filterBranchAndAge()
{
    qDebug() << "== Employees from New York and age below 40 =============";

    QSqlQuery query;
    if (query.exec("SELECT emp_name, emp_age, dep_name, brh_name FROM (SELECT emp_name, emp_age, emp_departmentID FROM employee) AS myEmployee INNER JOIN department ON department.dep_id = myEmployee.emp_departmentID INNER JOIN branch ON branch.brh_id = department.dep_branchID WHERE branch.brh_name = 'New York' AND myEmployee.emp_age < 40"))
    {
        while (query.next())
        {
            qDebug() << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }
}

void countFemale()
{
    qDebug() << "== Count female employees =============";

    QSqlQuery query;
    if (query.exec("SELECT COUNT(emp_gender) FROM employee WHERE emp_gender = 1"))
    {
        while (query.next())
        {
            qDebug() << query.value(0).toString();
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }
}

void filterName()
{
    qDebug() << "== Employees name start with 'Ja' =============";

    QSqlQuery query;
    if (query.exec("SELECT emp_name FROM employee WHERE emp_name LIKE '%Ja%'"))
    {
        while (query.next())
        {
            qDebug() << query.value(0).toString();
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }
}

void filterBirthday()
{
    qDebug() << "== Employees birthday in August =============";

    QSqlQuery query;
    if (query.exec("SELECT emp_name, emp_birthday FROM employee WHERE strftime('%m', emp_birthday) = '08'"))
    {
        while (query.next())
        {
            qDebug() << query.value(0).toString() << query.value(1).toDate().toString("d-MMMM-yyyy");
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }
}

void checkLog()
{
    qDebug() << "== Employees who logged in on 27 April 2024 =============";

    QSqlQuery query;
    if (query.exec("SELECT DISTINCT emp_name FROM (SELECT emp_id, emp_name FROM employee) AS myEmployee INNER JOIN user ON user.user_employeeID = myEmployee.emp_id INNER JOIN log ON log.log_userID = user.user_id WHERE DATE(log.log_loginTime) = '2024-04-27'"))
    {
        while (query.next())
        {
            qDebug() << query.value(0).toString();
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/User/Desktop/book/Qt5-CPP-GUI-Programming-Cookbook-Second-Edition/Chapter11/Advanced_SQL/database.db3");

    if (db.open())
    {
        filterAge();
        getDepartmentAndBranch();
        filterBranchAndAge();
        countFemale();
        filterName();
        filterBirthday();
        checkLog();

        db.close();
    }
    else
    {
        qDebug() << "Failed to connect to database.";
    }

    return a.exec();
}
