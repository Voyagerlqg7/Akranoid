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
	//Проверка перед началом игры, если что-то запущено то аннулируем 
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

	//Сброс значений переменных
	m_score = 0;
	m_paused = false;
	m_timerID = 0;
	m_score_mult = 0;
	m_game_over = false;
	m_paused = false;
	m_new_game = true;

	//Объект ракетки
	m_paddle = new Item();
	QImage paddle_image("");   //!!!IMAGE NOT SELECTED YET!!!
	//m_paddle->setImage(paddle_image);
	//m_paddle->setCords(QPoint(M_WIDTH/2 - paddle_image.width()/2, M_HEIGHT - M_PADDLE_Y_FROM_BOTTOM_BORDER));

	//Объекты кирпичей
	QImage brick_image();
	qreal widget_width = this->width();

	for (int h = 0; h < M_BRICKS_IN_HEIGHT; h++) {
		int y = M_BRICK_Y_FROM_TOP_BORDER + h * brick_image.height();
		for (int w = 0; w < M_BRICKS_IN_WIDTH; w++) {
			m_bricks.push_back(new Item());
			m_bricks.at(m_bricks.size() - 1)->setImage(brick_image);
			int x;
			// Рассчитываем расположение кирпичей по горизонтали
			// для корректного отображения их по центру

			if (M_BRICKS_IN_WIDTH % 2 == 0) { //Если четное кол-во кирпичей по горизонтали
				x = widget_width / 2 - M_BRICKS_IN_WIDTH / 2 * brick_image.width() + w * brick_image.width();
			}
			else {
				x = widget_width / 2 - M_BRICKS_IN_WIDTH / 2 * brick_image.width() - brick_image.width() / 2 + w * brick_image.width();
				m_bricks.at(m_bricks.size() - 1)->setCords(QPoint(x, y));
			}
		}
	}

	//Объект мячика, текстура и начальное положение
	m_ball = new Item();
	//m_ball->setImage(QImage());
	m_ball->setCords(QPoint(
		m_paddle->getCords().x() + paddle_image.width() / 2,
		m_paddle->getCords().y() - paddle_image.height() / 2));

	m_xdir = 1;
	m_ydir = -1;

}

void Arkanoid::startGame() {
	if (m_timerID == 0) {
		m_timerID = startTimer(M_DELAY);
		m_paused = false;
		m_new_game - false;
	}
}

void Arkanoid::pauseGame() {
	killTimer(m_timerID);
	m_timerID = 0;
	m_paused = true;
}
void Arkanoid::ballMove() {
	int add_x = 0;
	int add_y = 0;
	if (m_xdir == 1)
		add_x++;
	else if (m_xdir == -1)
		add_x--;

	if (m_ydir == 1)
		add_y++;
	else if (m_ydir == -1)
		add_y--;

	QPoint temp = m_ball->getCords();
	int x = temp.x(); +add_x;
	int y = temp.y() + add_y;
	m_ball->setCords(QPoint(x, y));
}

//Обработка столкновений шарика
void Arkanoid::checkBallTouch() {
	QPoint ball_cords = m_ball->getCords();
	QImage ball_image = m_ball->getImage();
	//.....
}

void Arkanoid::paintGameField(QPainter* painter) {
	for (auto& brick : m_bricks) {
		painter->drawImage(brick->getCords(), brick->getImage());
	}
	painter->drawImage(m_ball->getCords(), m_ball->getImage());
}

void Arkanoid::paintText(QPainter* painter, qreal x, qreal y,
	QString text, QFont font, QColor pen,
	QColor brush)
{
	QFontMetrics metrics(font);
	qreal text_width = metrics.horizontalAdvance(text);
	QPainterPath path;
	path.addText(x, y, font, text);
	painter->setPen(QPen(pen));
	painter->setBrush(QBrush(brush));
	painter->drawPath(path);
}

//Обработка прорисовки главного виджета
void Arkanoid::paintEvent(QPaintEvent* event) {

}

//Обработчик таймера
void Arkanoid::timerEvent(QTimerEvent* time_event) {

}

//Обработчик нажатия клавиш 
void Arkanoid::keyPressEvent(QKeyEvent* key_event) {

}