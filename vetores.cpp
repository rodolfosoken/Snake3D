#include <array>
#include <memory>
#include <vector>
#include <QDebug>

int main(int argc, char *argv[])
{
    double vx,vy,vz;
    double v1[3];
    std::array<double,3> v2;
    std::vector<double> v3;
    std::unique_ptr<double[]> v4;
    double *v5;
    vx=0;vy=1;vz=2;
    v1[0] = 0;
    v1[1] = 1;
    v1[2] = 2;
    qDebug() << v1[0] << v1[1] << v1[2];
    v2[0] = 0;
    v2[1] = 1;
    v2[2] = 2;
    qDebug() << v2[0] << v2[1] << v2[2];
    v3.resize(3);
    v3[0] = 0;
    v3[1] = 1;
    v3[2] = 2;
    qDebug() << v3[0] << v3[1] << v3[2];
    v4 = std::make_unique<double[]>(3);
    v4[0] = 0;
    v4[1] = 1;
    v4[2] = 2;
    qDebug() << v4[0] << v4[1] << v4[2];
    v5 = new double[3];
    v5[0] = 0;
    v5[1] = 1;
    v5[2] = 2;
    qDebug() << v5[0] << v5[1] << v5[2];
    delete []v5;
}
