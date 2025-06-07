#include "utils.h"

namespace CW {

    namespace angle {

        // ��������� ��������, � ������� ����� ����
        // ��������� ���� ����� �:
        //   0    -> I ��������
        //   90   -> II ��������
        //   -90  -> III ��������
        //   -180 -> IV ��������
        Quarter quarter(sf::Angle angle)
        {
            float fAngle = angle.wrapSigned().asRadians();

            if (fAngle >= 0.0f && fAngle < PI_2)
                return Quarter::First;
            if (fAngle >= PI_2 && fAngle < PI)
                return Quarter::Second;
            if (fAngle >= -PI && fAngle < -PI_2)
                return Quarter::Third;
            return Quarter::Fourth;
        }

    }

    sf::Vector2f ONE_LENGTH_VEC = { 1.0f, 0.0f };

} // CW
