/*
 Copyright (C) 2010-2014 Kristian Duske
 
 This file is part of TrenchBroom.
 
 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with TrenchBroom. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __TrenchBroom__TexturingViewScaleTool__
#define __TrenchBroom__TexturingViewScaleTool__

#include "Hit.h"
#include "Renderer/VertexSpec.h"
#include "View/Tool.h"
#include "View/ViewTypes.h"

namespace TrenchBroom {
    namespace Assets {
        class Texture;
    }
    
    namespace Renderer {
        class OrthographicCamera;
        class RenderContext;
    }
    
    namespace View {
        class TexturingViewHelper;
        
        class TexturingViewScaleTool : public ToolImpl<NoActivationPolicy, PickingPolicy, NoMousePolicy, MouseDragPolicy, NoDropPolicy, RenderPolicy> {
        public:
            static const Hit::HitType XHandleHit;
            static const Hit::HitType YHandleHit;
        private:
            static const FloatType MaxPickDistance;
            
            typedef Renderer::VertexSpecs::P3C4::Vertex EdgeVertex;
            
            class ScaleHandle {
            private:
                Vec2i m_index;
                Vec2f m_position;
                bool m_dragging[2];
            public:
                ScaleHandle();
                
                void reset();
                void setX(int index, const Assets::Texture* texture, const Vec2i& subDivisions);
                void setY(int index, const Assets::Texture* texture, const Vec2i& subDivisions);
            private:
                void set(size_t coord, int index, float position);
            public:
                const Vec2f& position() const;
                const Vec2f selector() const;
            };
            
            TexturingViewHelper& m_helper;
            Renderer::OrthographicCamera& m_camera;
            
            ScaleHandle m_scaleHandle;
            Vec2f m_lastPoint;
            Vec2f m_lastScaleDistance;
        public:
            TexturingViewScaleTool(MapDocumentWPtr document, ControllerWPtr controller, TexturingViewHelper& helper, Renderer::OrthographicCamera& camera);
        private:
            void doPick(const InputState& inputState, Hits& hits);

            bool doStartMouseDrag(const InputState& inputState);
            bool doMouseDrag(const InputState& inputState);
            void doEndMouseDrag(const InputState& inputState);
            void doCancelMouseDrag(const InputState& inputState);
            
            void doRender(const InputState& inputState, Renderer::RenderContext& renderContext);
            EdgeVertex::List getHandleVertices(const Hits& hits) const;
        };
    }
}

#endif /* defined(__TrenchBroom__TexturingViewScaleTool__) */
