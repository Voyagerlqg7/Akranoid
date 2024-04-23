#include <QPainter>
#include <QKeyEvent>
#include <QPainterPath>
#include "Arkanoid.h"

Arkanoid::Arkanoid(QWidget* parent)
	: QWidget(parent),
	m_paddle(),
	m_bricks(),
	m_ball(),
	m_xdir(0),
	m_ydir(0),
	m_timerID(0),
	m_score(0),
	m_score_mult(1),
	m_game_over(false),
	m_paused(false),
	m_new_game(true)
	//Список инициализации
{
	this->setFixedSize(M_WIDTH, M_HEIGHT); //Установка размера виджета
	this->setStyleSheet("background-color: black");
	newGame(); //start game
}

Arkanoid::~Arkanoid() {
	//Clear memory
	delete m_paddle;
	for (auto& brick : m_bricks) {
		delete brick;
	}
	m_bricks.clear();
	delete m_ball;
}

void Arkanoid::newGame() {

}

void Arkanoid::startGame() {

}

void Arkanoid::pauseGame() {

}
void Arkanoid::ballMove() {

}

void Arkanoid::checkBallTouch() {

}

void Arkanoid::paintGameField(QPainter* painter) {

}

void Arkanoid::paintText(QPainter* painter, qreal x, qreal y,
	QString text, QFont font, QColor pen,
	QColor brush)
{

}

void Arkanoid::paintEvent(QPaintEvent* event) {

}

void Arkanoid::timerEvent(QTimerEvent* time_event) {

}

void Arkanoid::keyPressEvent(QKeyEvent* key_event) {

}