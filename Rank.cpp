#include "Rank.h"

Rank::Rank(const QString &name) : name(name) {
}

Rank::Rank(const char *name) : Rank(QString(name)) {
}
