/*
 * Copyright 2020  Paul McAuley <kde@paulmcauley.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stylekite.h"

namespace Breeze
{
    void RenderStyleKite18By18::renderCloseIcon()
    {
        // slightly larger X to tie-in with design of square maximize button
        painter->drawLine( QPointF( 4.5, 4.5 ), QPointF( 13.5, 13.5 ) );
        painter->drawLine( QPointF(13.5, 4.5), QPointF(4.5, 13.5) );
    }
    
    void RenderStyleKite18By18::renderMaximizeIcon()
    {
        //large square
        pen.setJoinStyle( Qt::RoundJoin );
        painter->setPen( pen );

        painter->drawRect( QRectF( QPointF( 4.5, 4.5 ), QPointF( 13.5, 13.5 ) ) );
    }
    
    void RenderStyleKite18By18::renderMinimizeIcon()
    {
        //tiny filled square
        pen.setJoinStyle( Qt::RoundJoin );
        painter->setBrush( pen.color() );
        painter->setPen( pen );

        painter->drawRect( QRectF( QPointF( 7.5, 7.5 ), QPointF( 10.5, 10.5 ) ) );
    }
    

// For consistency with breeze icon set
    void RenderStyleKite18By18::renderKeepBehindIcon()
    {
        //horizontal lines
        painter->drawLine( QPointF( 4.5, 13.5 ), QPointF( 13.5, 13.5 ) );
        painter->drawLine( QPointF( 9.5, 9.5 ), QPointF( 13.5, 9.5 ) );
        painter->drawLine( QPointF( 9.5, 5.5 ), QPointF( 13.5, 5.5 ) );
        
        //arrow
        painter->drawLine( QPointF( 4.5, 3.5 ), QPointF( 4.5, 11.5 ) );
        
        painter->drawPolyline( QVector<QPointF>{
            QPointF( 2.5, 9.5 ),
            QPointF( 4.5, 11.5 ),
            QPointF( 6.5, 9.5 )} );
    }
    
    void RenderStyleKite18By18::renderKeepInFrontIcon()
    {
        //horizontal lines
        painter->drawLine( QPointF( 4.5, 4.5 ), QPointF( 13.5, 4.5 ) );
        painter->drawLine( QPointF( 4.5, 8.5 ), QPointF( 8.5, 8.5 ) );
        painter->drawLine( QPointF( 4.5, 12.5 ), QPointF( 8.5, 12.5 ) );
        
        //arrow
        painter->drawLine( QPointF( 13.5, 6.5 ), QPointF( 13.5, 14.5 ) );
        
        painter->drawPolyline( QVector<QPointF>{
            QPointF( 11.5, 8.5 ),
            QPointF( 13.5, 6.5 ),
            QPointF( 15.5, 8.5 )} );
    }



}
