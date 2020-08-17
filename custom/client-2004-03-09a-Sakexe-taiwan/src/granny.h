/// @custom
/// @version 2.1.5.0 (?)
#pragma once
struct granny_mesh;
struct granny_skeleton;
struct granny_track_group;
struct granny_grn_file_header;
struct granny_vertex_data;
struct granny_tri_topology;
struct granny_material;
struct granny_texture;
struct granny_string_table;


typedef int granny_int32; // 157
typedef float granny_real32; // 162
typedef granny_int32 granny_int32x; // 170


struct granny_transform // 1111
{
	/* this+0x0  */ unsigned int Flags;
	/* this+0x4  */ float Position[3];
	/* this+0x10 */ float Orientation[4];
	/* this+0x20 */ float ScaleShear[3][3];
};


struct granny_model_mesh_binding // 1123
{
	/* this+0x0 */ granny_mesh* Mesh;
};


struct granny_model // 1129
{
	/* this+0x0  */ char* Name;
	/* this+0x4  */ granny_skeleton* Skeleton;
	/* this+0x8  */ granny_transform InitialPlacement;
	/* this+0x4C */ int MeshBindingCount;
	/* this+0x50 */ granny_model_mesh_binding* MeshBindings;
};


struct granny_model_instance; // 1149


struct granny_data_type_definition // 1151
{
	/* this+0x0  */ enum granny_member_type Type;
	/* this+0x4  */ const char* Name;
	/* this+0x8  */ granny_data_type_definition* ReferenceType;
	/* this+0xC  */ int ArrayWidth;
	/* this+0x10 */ int Extra[3];
	/* this+0x1C */ unsigned int TraversalID;
};


struct granny_variant // 1167
{
	/* this+0x0 */ granny_data_type_definition* Type;
	/* this+0x4 */ void* Object;
};


struct granny_light_info // ????
{
	/* this+0x0 */ granny_variant ExtendedData;
};


struct granny_camera_info // ????
{
	/* this+0x0 */ granny_variant ExtendedData;
};


struct granny_curve // 1175
{
	/* this+0x0  */ int Degree;
	/* this+0x4  */ int KnotCount;
	/* this+0x8  */ float* Knots;
	/* this+0xC  */ int ControlCount;
	/* this+0x10 */ float* Controls;
};


struct granny_material_map // 1477
{
	/* this+0x0 */ char* Usage;
	/* this+0x4 */ granny_material* Material;
};


struct granny_material // 1485
{
	/* this+0x0  */ char* Name;
	/* this+0x4  */ int MapCount;
	/* this+0x8  */ granny_material_map* Maps;
	/* this+0xC  */ granny_texture* Texture;
	/* this+0x10 */ granny_variant ExtendedData;
};


struct granny_pixel_layout // 1499
{
	/* this+0x0  */ int BytesPerPixel;
	/* this+0x4  */ int ShiftForComponent[4];
	/* this+0x14 */ int BitsForComponent[4];
};


struct granny_animation // 1509
{
	/* this+0x0  */ char* Name;
	/* this+0x4  */ float Duration;
	/* this+0x8  */ float TimeStep;
	/* this+0xC  */ int TrackGroupCount;
	/* this+0x10 */ granny_track_group** TrackGroups;
};


struct granny_art_tool_info // 1562
{
	/* this+0x0  */ char* FromArtToolName;
	/* this+0x4  */ int ArtToolMajorRevision;
	/* this+0x8  */ int ArtToolMinorRevision;
	/* this+0xC  */ float UnitsPerMeter;
	/* this+0x10 */ float Origin[3];
	/* this+0x1C */ float RightVector[3];
	/* this+0x28 */ float UpVector[3];
	/* this+0x34 */ float BackVector[3];
};


struct granny_camera // 1594
{
	/* this+0x0   */ float WpOverHp;
	/* this+0x4   */ float WrOverHr;
	/* this+0x8   */ float WwOverHw;
	/* this+0xC   */ float FOVY;
	/* this+0x10  */ float NearClipPlane;
	/* this+0x14  */ float FarClipPlane;
	/* this+0x18  */ float Orientation[4];
	/* this+0x28  */ float Position[3];
	/* this+0x34  */ float EAR[3];
	/* this+0x40  */ float Offset[3];
	/* this+0x4C  */ float View4x4[4][4];
	/* this+0x8C  */ float InverseView4x4[4][4];
	/* this+0xCC  */ float Projection4x4[4][4];
	/* this+0x10C */ float InverseProjection4x4[4][4];
};


struct granny_control; // 1631


struct granny_exporter_info // 1641
{
	/* this+0x0  */ char* ExporterName;
	/* this+0x4  */ int ExporterMajorRevision;
	/* this+0x8  */ int ExporterMinorRevision;
	/* this+0xC  */ int ExporterCustomization;
	/* this+0x10 */ int ExporterBuildNumber;
};


struct granny_file // 1657
{
	/* this+0x0  */ unsigned char IsByteReversed;
	/* this+0x4  */ granny_grn_file_header* Header;
	/* this+0x8  */ int SectionCount;
	/* this+0xC  */ void** Sections;
	/* this+0x10 */ unsigned char* Marshalled;
	/* this+0x14 */ void* ConversionBuffer;
};


struct granny_grn_reference // 1697
{
	/* this+0x0 */ unsigned int SectionIndex;
	/* this+0x4 */ unsigned int Offset;
};


struct granny_grn_file_header // 1749
{
	/* this+0x0  */ unsigned int Version;
	/* this+0x4  */ unsigned int TotalSize;
	/* this+0x8  */ unsigned int CRC;
	/* this+0xC  */ unsigned int SectionArrayOffset;
	/* this+0x10 */ unsigned int SectionArrayCount;
	/* this+0x14 */ granny_grn_reference RootObjectTypeDefinition;
	/* this+0x1C */ granny_grn_reference RootObject;
	/* this+0x24 */ unsigned int TypeTag;
	/* this+0x28 */ unsigned int ExtraTags[4];
};


struct granny_file_info // 1775
{
	/* this+0x0  */ granny_string_table* FileStringTable;
	/* this+0x4  */ granny_art_tool_info* ArtToolInfo;
	/* this+0x8  */ granny_exporter_info* ExporterInfo;
	/* this+0xC  */ char* FromFileName;
	/* this+0x10 */ int TextureCount;
	/* this+0x14 */ granny_texture** Textures;
	/* this+0x18 */ int MaterialCount;
	/* this+0x1C */ granny_material** Materials;
	/* this+0x20 */ int SkeletonCount;
	/* this+0x24 */ granny_skeleton** Skeletons;
	/* this+0x28 */ int VertexDataCount;
	/* this+0x2C */ granny_vertex_data** VertexDatas;
	/* this+0x30 */ int TriTopologyCount;
	/* this+0x34 */ granny_tri_topology** TriTopologies;
	/* this+0x38 */ int MeshCount;
	/* this+0x3C */ granny_mesh** Meshes;
	/* this+0x40 */ int ModelCount;
	/* this+0x44 */ granny_model** Models;
	/* this+0x48 */ int TrackGroupCount;
	/* this+0x4C */ granny_track_group** TrackGroups;
	/* this+0x50 */ int AnimationCount;
	/* this+0x54 */ granny_animation** Animations;
};


struct granny_local_pose; // 1883


struct granny_bone_binding // 1904
{
	/* this+0x0  */ char* BoneName;
	/* this+0x4  */ float OBBMin[3];
	/* this+0x10 */ float OBBMax[3];
	/* this+0x1C */ int TriangleCount;
	/* this+0x20 */ int* TriangleIndices;
};


struct granny_material_binding // 1918
{
	/* this+0x0 */ granny_material* Material;
};


struct granny_morph_target // 1924
{
	/* this+0x0 */ char* ScalarName;
	/* this+0x4 */ granny_vertex_data* VertexData;
};


struct granny_mesh // 1934
{
	/* this+0x0  */ char* Name;
	/* this+0x4  */ granny_vertex_data* PrimaryVertexData;
	/* this+0x8  */ int MorphTargetCount;
	/* this+0xC  */ granny_morph_target* MorphTargets;
	/* this+0x10 */ granny_tri_topology* PrimaryTopology;
	/* this+0x14 */ int MaterialBindingCount;
	/* this+0x18 */ granny_material_binding* MaterialBindings;
	/* this+0x1C */ int BoneBindingCount;
	/* this+0x20 */ granny_bone_binding* BoneBindings;
	/* this+0x24 */ granny_variant ExtendedData;
};


struct granny_mesh_binding; // 1958


struct granny_mesh_deformer; // 1962


struct granny_periodic_loop // 1966
{
	/* this+0x0  */ float Radius;
	/* this+0x4  */ float dAngle;
	/* this+0x8  */ float dZ;
	/* this+0xC  */ float BasisX[3];
	/* this+0x18 */ float BasisY[3];
	/* this+0x24 */ float Axis[3];
};


struct granny_bone // 1984
{
	/* this+0x0  */ char* Name;
	/* this+0x4  */ int ParentIndex;
	/* this+0x8  */ granny_transform LocalTransform;
	/* this+0x4C */ float InverseWorld4x4[4][4];
	/* this+0x8C */ granny_light_info* LightInfo;
	/* this+0x90 */ granny_camera_info* CameraInfo;
	/* this+0x94 */ granny_variant ExtendedData;
};


struct granny_skeleton // 2000
{
	/* this+0x0 */ char* Name;
	/* this+0x4 */ int BoneCount;
	/* this+0x8 */ granny_bone* Bones;
};


struct granny_string_table // 2278
{
	/* this+0x0 */ int StringCount;
	/* this+0x4 */ int* StringOffsets;
	/* this+0x8 */ int CharacterCount;
	/* this+0xC */ unsigned char* Characters;
};


struct granny_system_clock // 2280
{
	/* this+0x0 */ unsigned int Data[4];
};


struct granny_texture_mip_level // 2295
{
	/* this+0x0 */ int Stride;
	/* this+0x4 */ int Size;
	/* this+0x8 */ void* Pixels;
};


struct granny_texture_image // 2305
{
	/* this+0x0 */ int MIPLevelCount;
	/* this+0x4 */ granny_texture_mip_level* MIPLevels;
};


struct granny_texture // 2313
{
	/* this+0x0  */ char* FromFileName;
	/* this+0x4  */ int TextureType;
	/* this+0x8  */ int Width;
	/* this+0xC  */ int Height;
	/* this+0x10 */ int Encoding;
	/* this+0x14 */ int SubFormat;
	/* this+0x18 */ granny_pixel_layout Layout;
	/* this+0x3C */ int ImageCount;
	/* this+0x40 */ granny_texture_image* Images;
	/* this+0x44 */ granny_variant ExtendedData;
};


struct granny_scalar_track // 2339
{
	/* this+0x0 */ char* Name;
	/* this+0x4 */ granny_curve ValueCurve;
};


struct granny_transform_track // 2351
{
	/* this+0x0  */ char* Name;
	/* this+0x4  */ granny_curve PositionCurve;
	/* this+0x18 */ granny_curve OrientationCurve;
	/* this+0x2C */ granny_curve ScaleShearCurve;
};


struct granny_text_track_entry // 2365
{
	/* this+0x0 */ float TimeStamp;
	/* this+0x4 */ char* Text;
};


struct granny_text_track // 2373
{
	/* this+0x0 */ char* Name;
	/* this+0x4 */ int EntryCount;
	/* this+0x8 */ granny_text_track_entry* Entries;
};


struct granny_track_group // 2383
{
	/* this+0x0  */ char* Name;
	/* this+0x4  */ int ScalarTrackCount;
	/* this+0x8  */ granny_scalar_track* ScalarTracks;
	/* this+0xC  */ int TransformTrackCount;
	/* this+0x10 */ granny_transform_track* TransformTracks;
	/* this+0x14 */ int TextTrackCount;
	/* this+0x18 */ granny_text_track* TextTracks;
	/* this+0x1C */ granny_transform InitialPlacement;
	/* this+0x60 */ int AccumulationFlags;
	/* this+0x64 */ float LoopTranslation[3];
	/* this+0x70 */ granny_periodic_loop* PeriodicLoop;
	/* this+0x74 */ granny_variant ExtendedData;
};


struct granny_tri_material_group // 2450
{
	/* this+0x0 */ int MaterialIndex;
	/* this+0x4 */ int TriFirst;
	/* this+0x8 */ int TriCount;
};


struct granny_tri_annotation_set // 2460
{
	/* this+0x0  */ const char* Name;
	/* this+0x4  */ granny_data_type_definition* TriAnnotationType;
	/* this+0x8  */ int TriAnnotationCount;
	/* this+0xC  */ unsigned char* TriAnnotations;
	/* this+0x10 */ int TriAnnotationIndexCount;
	/* this+0x14 */ int* TriAnnotationIndices;
};


struct granny_tri_topology // 2478
{
	/* this+0x0  */ int GroupCount;
	/* this+0x4  */ granny_tri_material_group* Groups;
	/* this+0x8  */ int IndexCount;
	/* this+0xC  */ int* Indices;
	/* this+0x10 */ int IndexCount16;
	/* this+0x14 */ unsigned short* Indices16;
	/* this+0x18 */ int VertexToVertexCount;
	/* this+0x1C */ int* VertexToVertexMap;
	/* this+0x20 */ int VertexToTriangleCount;
	/* this+0x24 */ int* VertexToTriangleMap;
	/* this+0x28 */ int SideToNeighborCount;
	/* this+0x2C */ unsigned int* SideToNeighborMap;
	/* this+0x30 */ int BonesForTriangleCount;
	/* this+0x34 */ int* BonesForTriangle;
	/* this+0x38 */ int TriangleToBoneCount;
	/* this+0x3C */ int* TriangleToBoneIndices;
	/* this+0x40 */ int TriAnnotationSetCount;
	/* this+0x44 */ granny_tri_annotation_set* TriAnnotationSets;
};


struct granny_vertex_annotation_set // 2527
{
	/* this+0x0  */ const char* Name;
	/* this+0x4  */ granny_data_type_definition* VertexAnnotationType;
	/* this+0x8  */ int VertexAnnotationCount;
	/* this+0xC  */ unsigned char* VertexAnnotations;
	/* this+0x10 */ int VertexAnnotationIndexCount;
	/* this+0x14 */ int* VertexAnnotationIndices;
};


struct granny_vertex_data // 2545
{
	/* this+0x0  */ granny_data_type_definition* VertexType;
	/* this+0x4  */ int VertexCount;
	/* this+0x8  */ unsigned char* Vertices;
	/* this+0xC  */ int VertexAnnotationSetCount;
	/* this+0x10 */ granny_vertex_annotation_set* VertexAnnotationSets;
};


struct granny_pnt332_vertex // 2631
{
	/* this+0x0  */ float Position[3];
	/* this+0xC  */ float Normal[3];
	/* this+0x18 */ float UV[2];
};


struct granny_world_pose; // 2945


granny_model_instance* __stdcall GrannyInstantiateModel(granny_model const * Model); // 3013

granny_skeleton* __stdcall GrannyGetSourceSkeleton(granny_model_instance const* Model); // 3016
void __stdcall GrannySetModelClock(granny_model_instance const* ModelInstance, granny_real32 NewClock); // 3017
void __stdcall GrannyFreeCompletedModelControls(granny_model_instance const* ModelInstance); // 3019

void __stdcall GrannySampleModelAnimations(granny_model_instance const* ModelInstance, granny_int32x FirstBone, granny_int32x BoneCount, granny_local_pose* Result); // 3049

void __stdcall GrannyFreeControl(granny_control* Control); // 3716

float __stdcall GrannyGetControlDurationLeft(granny_control* Control); // 3752
bool __stdcall GrannyControlIsActive(granny_control const* Control); // 3753
void __stdcall GrannySetControlActive(granny_control* Control, bool Active); // 3754

granny_int32x __stdcall GrannyGetMeshIndexCount(granny_mesh const* Mesh); // 4609

granny_system_clock __stdcall GrannyGetSystemSeconds(); // 4948
float __stdcall GrannyGetSecondsElapsed(const granny_system_clock* StartClock, const granny_system_clock* EndClock); // 4949

void __stdcall GrannyBuildWorldPose(granny_skeleton const* Skeleton, granny_int32x FirstBone, granny_int32x BoneCount, granny_local_pose const* LocalPose, granny_real32 const* Offset4x4, granny_world_pose* Result); // 5417
