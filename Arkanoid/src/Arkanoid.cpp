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
	//������ �������������
{
	this->setFixedSize(M_WIDTH, M_HEIGHT); //��������� ������� �������
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
	//�������� ����� ������� ����, ���� ���-�� �������� �� ���������� 
	if (m_paddle != nullptr) { delete m_paddle; }

	for (auto& brick : m_bricks) {
		if (brick != nullptr) {
			delete brick;
			brick = nullptr;
		}
	}

	m_bricks.clear();
	if (m_ball != nullptr) { delete m_ball; }
	if (m_timerID != 0) { killTimer(m_timerID); }

	//����� �������� ����������
	m_score = 0;
	m_paused = false;
	m_timerID = 0;
	m_score_mult = 0;
	m_game_over = false;
	m_paused = false;
	m_new_game = true;

	//������ �������
	m_paddle = new Item();
	QImage paddle_image("");   //!!!IMAGE NOT SELECTED YET!!!
	//m_paddle->setImage(paddle_image);
	//m_paddle->setCords(QPoint(M_WIDTH/2 - paddle_image.width()/2, M_HEIGHT - M_PADDLE_Y_FROM_BOTTOM_BORDER));

	//������� ��������
	//QImage brick_image();
	qreal widget_width = this->width();

	/*for () {

		for () {

		}

	}*/

	//������ ������, �������� � ��������� ���������
	m_ball = new Item();
	//m_ball->setImage(QImage());
	m_ball->setCords(QPoint(
		m_paddle->getCords().x() + paddle_image.width() / 2,
		m_paddle->getCords().y() - paddle_image.height() / 2));
	m_xdir = 1;
	m_ydir = -1;

}

void Arkanoid::startGame() {

}

void Arkanoid::pauseGame() {
	killTimer(m_timerID);
	m_timerID = 0;
	m_paused = true;
}
void Arkanoid::ballMove() {

}

//��������� ������������ ������
void Arkanoid::checkBallTouch() {
	QPoint ball_cords = m_ball->getCords();
	QImage ball_image = m_ball->getImage();
	//.....
}

void Arkanoid::paintGameField(QPainter* painter) {

}

void Arkanoid::paintText(QPainter* painter, qreal x, qreal y,
	QString text, QFont font, QColor pen,
	QColor brush)
{
	QFontMetrics metrics(font);
	qreal text_width = metrics.horizontalAdvance(text);
	QPainterPath path;


}

//��������� ���������� �������� �������
void Arkanoid::paintEvent(QPaintEvent* event) {

}

//���������� �������
void Arkanoid::timerEvent(QTimerEvent* time_event) {

}

//���������� ������� ������ 
void Arkanoid::keyPressEvent(QKeyEvent* key_event) {

}