/*
 * Hydrogen
 * Copyright(c) 2002-2005 by Alex >Comix< Cominu [comix@users.sourceforge.net]
 *
 * http://www.hydrogen-music.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY, without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * $Id: AboutDialog.h,v 1.6 2005/05/01 19:50:57 comix Exp $
 *
 */

#ifndef ABOUT__DIALOG_H
#define ABOUT__DIALOG_H

#include <qwidget.h>
#include "config.h"
#include "UI/AboutDialog_UI.h"

class AboutDialog : public AboutDialog_UI 
{
	Q_OBJECT
	public:
		AboutDialog(QWidget* parent);
		~AboutDialog();

	public slots:

	private:
		void okBtnClicked();

};

#endif

