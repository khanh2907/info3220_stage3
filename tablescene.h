#ifndef TABLESCENE_H
#define TABLESCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <vector>
#include <memory>

#include "tableview.h"
#include "ball.h"
#include "brick.h"
#include "paddle.h"

class TableScene : public QGraphicsScene
{
    Q_OBJECT

public:
    static TableScene * instance(int width, int height,
                                 QColor bgColour);

    void startAnimation(int framerate);
    QGraphicsView & view();

    TableScene & addBall(Ball *ball);
    Ball * getBall();

    TableScene & addBrick(Brick *brick);
    std::vector<Brick *> & getBricks();

    TableScene & addPaddle(Paddle *paddle);
    Paddle * getPaddle();

    virtual ~TableScene();

protected:
    TableScene(int width, int height,
               QColor bgColour);

    void stopAnimation();
    void restartAnimation();
    void toggleAnimation();

    virtual void keyPressEvent (QKeyEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    TableScene();
    static TableScene * m_table_instance;  /*!< the single TableScene instance */

    QTimer m_timer;     /*!< QTimer for scene refresh */
    TableView m_view;   /*!< TableView for displaying scene */
    Ball * m_ball;      /*!< Pointer to the ball */
    std::vector<Brick *> m_bricks; /*!< Vector of pointers to bricks */
    Paddle * m_paddle;

signals:

public slots:


};

#endif // TABLESCENE_H
