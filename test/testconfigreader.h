#ifndef TESTCONFIGREADER_H
#define TESTCONFIGREADER_H
#include "AutoTest.h"

class TestConfigReader : public QObject
{
    Q_OBJECT

private slots:
    void testBoxConfig();
    void testBallConfig();
    void testBricksConfig();
    void testExtensions();
};

DECLARE_TEST(TestConfigReader)

#endif // TESTCONFIGREADER_H

