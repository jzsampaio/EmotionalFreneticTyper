#include <cmath>
#include <algorithm>

#include "Rect.h"
#include "AxisAlignedBoundingBox.h"
#include "Collidable.h"

class Collision {

public:
    static bool IsColliding(Collidable *a, Collidable *b) {

        if (!a || !b)
            return false;
        if (a->is("AxisAlignedBoundingBox") && b->is("AxisAlignedBoundingBox")) {
            return Collision::IsColliding(((AxisAlignedBoundingBox *) a)->axisAlignedRectangle,
                                          ((AxisAlignedBoundingBox *) b)->axisAlignedRectangle,
                                          0, 0);
        }
        else {
            cerr << "Collision not supported!" << endl;
        }

    }

    // Observação: IsColliding espera ângulos em radianos!
    // Para usar graus, forneça a sua própria implementação de Rotate,
    // ou transforme os ângulos no corpo de IsColliding.
    static inline bool IsColliding(Rect &a, Rect &b, float angleOfA, float angleOfB) {
        Vec2 A[] = {Vec2(a.leftTopX, a.leftTopY + a.h),
                    Vec2(a.leftTopX + a.w, a.leftTopY + a.h),
                    Vec2(a.leftTopX + a.w, a.leftTopY),
                    Vec2(a.leftTopX, a.leftTopY)
        };
        Vec2 B[] = {Vec2(b.leftTopX, b.leftTopY + b.h),
                    Vec2(b.leftTopX + b.w, b.leftTopY + b.h),
                    Vec2(b.leftTopX + b.w, b.leftTopY),
                    Vec2(b.leftTopX, b.leftTopY)
        };

        for (auto &v : A) {
            v = Rotate(v - a.getCenter(), angleOfA) + a.getCenter();
        }

        for (auto &v : B) {
            v = Rotate(v - b.getCenter(), angleOfB) + b.getCenter();
        }

        Vec2 axes[] = {Norm(A[0] - A[1]), Norm(A[1] - A[2]), Norm(B[0] - B[1]), Norm(B[1] - B[2])};

        for (auto &axis : axes) {
            float P[4];

            for (int i = 0; i < 4; ++i) P[i] = Dot(A[i], axis);

            float minA = *std::min_element(P, P + 4);
            float maxA = *std::max_element(P, P + 4);

            for (int i = 0; i < 4; ++i) P[i] = Dot(B[i], axis);

            float minB = *std::min_element(P, P + 4);
            float maxB = *std::max_element(P, P + 4);

            if (maxA < minB || minA > maxB)
                return false;
        }

        return true;
    }

private:

    static inline float Mag(const Vec2 &p) {
        return std::sqrt(p.x * p.x + p.y * p.y);
    }

    static inline Vec2 Norm(const Vec2 &p) {
        return p * (1.f / Mag(p));
    }

    static inline float Dot(const Vec2 &a, const Vec2 &b) {
        return a.x * b.x + a.y * b.y;
    }

    static inline Vec2 Rotate(const Vec2 &p, float angle) {
        float cs = std::cos(angle), sn = std::sin(angle);
        return Vec2(p.x * cs - p.y * sn, p.x * sn + p.y * cs);
    }
};

