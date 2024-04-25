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
	QImage brick_image();
	qreal widget_width = this->width();

	for (int h = 0; h < M_BRICKS_IN_HEIGHT; h++) {
		int y = M_BRICK_Y_FROM_TOP_BORDER + h * brick_image.height();
		for (int w = 0; w < M_BRICKS_IN_WIDTH; w++) {
			m_bricks.push_back(new Item());
			m_bricks.at(m_bricks.size() - 1)->setImage(brick_image);
			int x;
			// ������������ ������������ �������� �� �����������
			// ��� ����������� ����������� �� �� ������

			if (M_BRICKS_IN_WIDTH % 2 == 0) { //���� ������ ���-�� �������� �� �����������
				x = widget_width / 2 - M_BRICKS_IN_WIDTH / 2 * brick_image.width() + w * brick_image.width();
			}
			else {
				x = widget_width / 2 - M_BRICKS_IN_WIDTH / 2 * brick_image.width() - brick_image.width() / 2 + w * brick_image.width();
				m_bricks.at(m_bricks.size() - 1)->setCords(QPoint(x, y));
			}
		}
	}

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

//��������� ������������ ������
void Arkanoid::checkBallTouch() {
	//��������� ���������� � �����������, �������� ������ � ����
	QPoint ball_cords = m_ball->getCords();
	QImage ball_image = m_ball->getImage();

	int ball_width = ball_image.width();
	int ball_height = ball_image.height();
	int widget_width = this->width();
	int widget_height = this->height();

	//�������� ������������ � ���������
	if (ball_cords.x() + ball_width > widget_width)
		m_xdir = -1;
	if (ball_cords.x() < 0)
		m_xdir = 1;
	if (ball_cords.y() < 0)
		m_ydir = 1;

	//���� ��� ���� ���� ������ �������, �� GAME OVER
	if (ball_cords.y() > widget_height) {
		killTimer(m_timerID);
		m_game_over = true;
	}

	//���� � ����������� � �������� �������
	QPoint paddle_cords = m_paddle->getCords();
	QImage paddle_image = m_paddle->getImage();
	int paddle_width = paddle_image.width();
	int paddle_height = paddle_image.height();

	//������������ ������ � ��������
	int racket_ball_collision = (ball_cords.y() + ball_height > paddle_cords.y()) &&
		(ball_cords.y() + ball_height < paddle_cords.y() + paddle_height) &&
		ball_cords.x() + ball_width / 2 > paddle_cords.x() &&
		ball_cords.x() - ball_width / 2 < paddle_cords.x() + paddle_width;

	//��������� � ����� �������
	int hit_in_center_of_paddle = ball_cords.x() + ball_width / 2 > paddle_cords.x() + paddle_width / 2 - ball_width / 2 &&
		ball_cords.x() + ball_width / 2 < paddle_cords.x() + paddle_width / 2 + ball_width / 2;

	//��������� � ������ �����
	int hit_in_right_part_of_paddle = ball_cords.x() + ball_width / 2 > paddle_cords.x() + paddle_width / 2;


	//������������ ������ � ��������
	if (racket_ball_collision)
	{
		m_ydir = -1;//����� ����������� �������� ������ �� Y
		//���� ����� ����� � ����� �������
		if (hit_in_center_of_paddle) {
			m_xdir = 0;//����� ����������� �� ��� X
			m_score_mult = 1;//����������� ��������������� �� 1
		}
		else if (hit_in_right_part_of_paddle) {
			m_xdir = 1;//����� ����������� �� ��� X
			m_score_mult = 1;//����������� ��������������� �� 1
		}
		else { //��������� � ����� �����, ������ �� �� �����
			m_xdir = -1;
			m_score_mult = 1;
		}
	}

	//������������ ������ � ���������
	for (size_t brick = 0; brick < m_bricks.size(); brick++)
	{
		//��������� ���������� ��� ������� ���� �������
		QPoint brick_cords = m_bricks.at(brick)->getCords();
		QImage brick_image = m_bricks.at(brick)->getImage();
		int brick_width = brick_image.width();
		int brick_height = brick_image.height();
		// ��������� �������� �� ����� ������� �����-�����,
		//  ���� ��������, �� ��������� ����, 
		// ������ ����������� �������� ������ � ������� ���� ������
		int hit_in_bottom_up = m_ydir == -1 && ball_cords.y() < brick_cords.y() + brick_height &&
			ball_cords.y() > brick_cords.y() &&
			ball_cords.x() + ball_width > brick_cords.x() &&
			ball_cords.x() < brick_cords.x() + brick_width;

		//��������� ������ ����
		int hiy_top_down = m_ydir == 1 && ball_cords.y() + ball_height > brick_cords.y() &&
			ball_cords.y() + ball_height < brick_cords.y() + brick_height &&
			ball_cords.x() + ball_width > brick_cords.x() &&
			ball_cords.x() < brick_cords.x() + brick_width;


		if (hit_in_bottom_up) {
			m_ydir = 1;//������ ����������� �������� ������ �� ��� Y
			m_score += 10 * m_score_mult;//���������� �����
			m_score_mult *= 2;
			if (ball_cords.x() + ball_width / 2 < brick_cords.x() + brick_width / 2)//��������� � ����� ����� �������
				m_xdir = -1;
			else
				m_xdir = 1;

			Item* temp = m_bricks.at(brick); // �������� ��������� �� ��������� ���������� ��� ������� ������
			m_bricks.remove(brick);
			delete temp;
		}
		else if (hiy_top_down)
		{
			m_ydir = -1;
			m_score += 20 * m_score_mult;
			m_score_mult *= 2;
			if (ball_cords.x() + ball_width / 2 < brick_cords.x() + brick_width / 2)
				m_xdir = -1;
			else
				m_xdir = 1;

			Item* temp = m_bricks.at(brick); // �������� ��������� �� ��������� ���������� ��� ������� ������
			m_bricks.remove(brick);
			delete temp;
		}
	}
}

void Arkanoid::paintGameField(QPainter* painter) {
	painter->drawImage(m_paddle->getCords(), m_paddle->getImage());
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

//��������� ���������� �������� �������
void Arkanoid::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event);
	qreal widget_width = this->width();
	qreal widget_height = this->height();
	QPainter* painter = new QPainter(this);

	//���� ���� �� ���������, ������ ����
	if (!m_game_over && m_bricks.size() > 0) {
		paintGameField(painter);
		QString text("Score: %1");
		text = text.arg(m_score);
		QFont font("Times new Roman", 14);
		QFontMetrics metrics(font);
		qreal text_width = metrics.horizontalAdvance(text);
		qreal text_width = metrics.height();
		paintText(painter, widget_width / 2 - text_width / 2, M_PADDLE_Y_FROM_BOTTOM_BORDER / 2, text, font, QColor("red"), QColor("red"));
		//��������� ��� ������ ����
		if (m_new_game) {
			QString text("To game begin click \"Space\"");
			QFont font("Times New Roman", 10);
			QFontMetrics metrics(font);
			qreal text_width = metrics.horizontalAdvance(text);
			qreal text_height = metrics.height();
			paintText(painter, widget_width / 2 - text_width / 2, widget_height - static_cast<qreal>(M_PADDLE_Y_FROM_BOTTOM_BORDER)
				/ 2 + text_height, text, font,
				QColor("orange"),
				QColor("black"));
		}
	}
	else if (m_bricks.size() > 0) {
		QString text("Game Over");
		QString score("your score: %1");
		score = score.arg(m_score);
		QFont text_font("Times New Roman", 32);
		QFont score_font("Times New Roman", 16);
		QFontMetrics text_metrics(text_font);
		QFontMetrics score_metrics(score_font);
		qreal text_width = text_metrics.horizontalAdvance(text);
		qreal score_width = score_metrics.horizontalAdvance(score);
		qreal score_height = score_metrics.height();
		paintText(painter, widget_width / 2 - text_width / 2, widget_height / 2, text, text_font,
			QColor("red"),
			QColor("black"));
		paintText(painter, widget_width / 2 - score_width / 2, widget_height / 2 + score_height, score, score_font,
			QColor("red"),
			QColor("red"));
	}
	else// ���� ��� ������� ����������
	{
		QString text("You win!");
		QString score("your score: %1");
		score = score.arg(m_score);
		QFont text_font("Times New Roman", 32);
		QFont score_font("Times New Roman", 16);
		QFontMetrics text_metrics(text_font);
		QFontMetrics score_metrics(score_font);
		qreal text_width = text_metrics.horizontalAdvance(text);
		qreal score_width = score_metrics.horizontalAdvance(score);
		qreal score_height = score_metrics.height();
		paintText(painter, widget_width / 2 - text_width / 2, widget_height / 2, text, text_font,
			QColor("black"),
			QColor("red"));
		paintText(painter, widget_width / 2 - score_width / 2, widget_height / 2 + score_height, score, score_font,
			QColor("red"),
			QColor("red"));
	}
	//�����
	if (m_paused) {
		QString text("To game continue click \"Space\", or \"Escape\", or \"P\"");
		QFont font("Times New Roman", 10);
		QFontMetrics metrics(font);
		qreal text_width = metrics.horizontalAdvance(text);
		qreal text_height = metrics.height();
		qreal widget_height = this->height();
		paintText(painter, widget_width / 2 - text_width / 2, widget_height - static_cast<qreal>(M_PADDLE_Y_FROM_BOTTOM_BORDER) / 2 + text_height, text, font,
			QColor("orange"),
			QColor("black"));
	}
}

//���������� �������
void Arkanoid::timerEvent(QTimerEvent* time_event) {
	Q_UNUSED(time_event);
	ballMove(); //�������� ������
	checkBallTouch(); //�������� ������������
	this->repaint(); //����������� �������
}

//���������� ������� ������ 
void Arkanoid::keyPressEvent(QKeyEvent* key_event) {

}