#version 120

// Packs the normalized depth into the vertex color.

//includes:
vec4 packDepth_impl( float z );

uniform mat4 worldview_matrix;

void packDepth_vert()
{
  vec4 pos_rel_view = worldview_matrix * gl_Vertex;
  gl_FrontColor = packDepth_impl( pos_rel_view.z );
}