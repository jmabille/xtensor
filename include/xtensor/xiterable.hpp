/***************************************************************************
* Copyright (c) 2016, Johan Mabille, Sylvain Corlay and Wolf Vollprecht    *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XTENSOR_ITERABLE_HPP
#define XTENSOR_ITERABLE_HPP

#include "xiterator.hpp"

namespace xt
{

    /*******************
     * xconst_iterable *
     *******************/

    template <class D>
    struct xiterable_inner_types;

#define DL XTENSOR_DEFAULT_LAYOUT

    /**
     * @class xconst_iterable
     * @brief Base class for multidimensional iterable constant expressions
     *
     * The xconst_iterable class defines the interface for multidimensional
     * constant expressions that can be iterated.
     *
     * @tparam D The derived type, i.e. the inheriting class for which xconst_iterable
     *           provides the interface.
     */
    template <class D>
    class xconst_iterable
    {
    public:

        using derived_type = D;

        using iterable_types = xiterable_inner_types<D>;
        using inner_shape_type = typename iterable_types::inner_shape_type;

        using stepper = typename iterable_types::stepper;
        using const_stepper = typename iterable_types::const_stepper;

        template <layout_type L>
        using layout_iterator = xiterator<stepper, inner_shape_type*, L>;
        template <layout_type L>
        using const_layout_iterator = xiterator<const_stepper, inner_shape_type*, L>;
        template <layout_type L>
        using reverse_layout_iterator = std::reverse_iterator<layout_iterator<L>>;
        template <layout_type L>
        using const_reverse_layout_iterator = std::reverse_iterator<const_layout_iterator<L>>;

        using storage_iterator = layout_iterator<DL>;
        using const_storage_iterator = const_layout_iterator<DL>;
        using reverse_storage_iterator = reverse_layout_iterator<DL>;
        using const_reverse_storage_iterator = const_reverse_layout_iterator<DL>;

        template <class S, layout_type L>
        using broadcast_iterator = xiterator<stepper, S, L>;
        template <class S, layout_type L>
        using const_broadcast_iterator = xiterator<const_stepper, S, L>;
        template <class S, layout_type L>
        using reverse_broadcast_iterator = std::reverse_iterator<broadcast_iterator<S, L>>;
        template <class S, layout_type L>
        using const_reverse_broadcast_iterator = std::reverse_iterator<const_broadcast_iterator<S, L>>;

        using iterator = layout_iterator<DL>;
        using const_iterator = const_layout_iterator<DL>;
        using reverse_iterator = reverse_layout_iterator<DL>;
        using const_reverse_iterator = const_reverse_layout_iterator<DL>;

        template <layout_type L = DL>
        const_layout_iterator<L> begin() const noexcept;
        template <layout_type L = DL>
        const_layout_iterator<L> end() const noexcept;
        template <layout_type L = DL>
        const_layout_iterator<L> cbegin() const noexcept;
        template <layout_type L = DL>
        const_layout_iterator<L> cend() const noexcept;

        template <layout_type L = DL>
        const_reverse_layout_iterator<L> rbegin() const noexcept;
        template <layout_type L = DL>
        const_reverse_layout_iterator<L> rend() const noexcept;
        template <layout_type L = DL>
        const_reverse_layout_iterator<L> crbegin() const noexcept;
        template <layout_type L = DL>
        const_reverse_layout_iterator<L> crend() const noexcept;

        template <class S, layout_type L = DL>
        const_broadcast_iterator<S, L> begin(const S& shape) const noexcept;
        template <class S, layout_type L = DL>
        const_broadcast_iterator<S, L> end(const S& shape) const noexcept;
        template <class S, layout_type L = DL>
        const_broadcast_iterator<S, L> cbegin(const S& shape) const noexcept;
        template <class S, layout_type L = DL>
        const_broadcast_iterator<S, L> cend(const S& shape) const noexcept;

        template <class S, layout_type L = DL>
        const_reverse_broadcast_iterator<S, L> rbegin(const S& shape) const noexcept;
        template <class S, layout_type L = DL>
        const_reverse_broadcast_iterator<S, L> rend(const S& shape) const noexcept;
        template <class S, layout_type L = DL>
        const_reverse_broadcast_iterator<S, L> crbegin(const S& shape) const noexcept;
        template <class S, layout_type L = DL>
        const_reverse_broadcast_iterator<S, L> crend(const S& shape) const noexcept;

        const_storage_iterator storage_begin() const noexcept;
        const_storage_iterator storage_end() const noexcept;
        const_storage_iterator storage_cbegin() const noexcept;
        const_storage_iterator storage_cend() const noexcept;

        const_reverse_storage_iterator storage_rbegin() const noexcept;
        const_reverse_storage_iterator storage_rend() const noexcept;
        const_reverse_storage_iterator storage_crbegin() const noexcept;
        const_reverse_storage_iterator storage_crend() const noexcept;

    protected:

        const inner_shape_type& get_shape() const;

    private:

        template <layout_type L>
        const_layout_iterator<L> get_cbegin(bool end_index) const noexcept;
        template <layout_type L>
        const_layout_iterator<L> get_cend(bool end_index) const noexcept;

        template <class S, layout_type L>
        const_broadcast_iterator<S, L> get_cbegin(const S& shape, bool end_index) const noexcept;
        template <class S, layout_type L>
        const_broadcast_iterator<S, L> get_cend(const S& shape, bool end_index) const noexcept;

        template <class S>
        const_stepper get_stepper_begin(const S& shape) const noexcept;
        template <class S>
        const_stepper get_stepper_end(const S& shape, layout_type l) const noexcept;

        const derived_type& derived_cast() const;
    };

    /*************
     * xiterable *
     *************/

    /**
     * @class xiterable
     * @brief Base class for multidimensional iterable expressions
     *
     * The xiterable class defines the interface for multidimensional
     * expressions that can be iterated.
     *
     * @tparam D The derived type, i.e. the inheriting class for which xiterable
     *           provides the interface.
     */
    template <class D>
    class xiterable : public xconst_iterable<D>
    {
    public:

        using derived_type = D;

        using base_type = xconst_iterable<D>;
        using inner_shape_type = typename base_type::inner_shape_type;

        using stepper = typename base_type::stepper;
        using const_stepper = typename base_type::const_stepper;

        using storage_iterator = typename base_type::storage_iterator;
        using reverse_storage_iterator = typename base_type::reverse_storage_iterator;

        template <layout_type L>
        using layout_iterator = typename base_type::template layout_iterator<L>;
        template <layout_type L>
        using const_layout_iterator = typename base_type::template const_layout_iterator<L>;
        template <layout_type L>
        using reverse_layout_iterator = typename base_type::template reverse_layout_iterator<L>;
        template <layout_type L>
        using const_reverse_layout_iterator = typename base_type::template const_reverse_layout_iterator<L>;

        template <class S, layout_type L>
        using broadcast_iterator = typename base_type::template broadcast_iterator<S, L>;
        template <class S, layout_type L>
        using const_broadcast_iterator = typename base_type::template const_broadcast_iterator<S, L>;
        template <class S, layout_type L>
        using reverse_broadcast_iterator = typename base_type::template reverse_broadcast_iterator<S, L>;
        template <class S, layout_type L>
        using const_reverse_broadcast_iterator = typename base_type::template const_reverse_broadcast_iterator<S, L>;

        using iterator = typename base_type::iterator;
        using const_iterator = typename base_type::const_iterator;
        using reverse_iterator = typename base_type::reverse_iterator;
        using const_reverse_iterator = typename base_type::const_reverse_iterator;

        using base_type::begin;
        using base_type::end;
        using base_type::rbegin;
        using base_type::rend;

        template <layout_type L = DL>
        layout_iterator<L> begin() noexcept;
        template <layout_type L = DL>
        layout_iterator<L> end() noexcept;

        template <layout_type L = DL>
        reverse_layout_iterator<L> rbegin() noexcept;
        template <layout_type L = DL>
        reverse_layout_iterator<L> rend() noexcept;

        template <class S, layout_type L = DL>
        broadcast_iterator<S, L> begin(const S& shape) noexcept;
        template <class S, layout_type L = DL>
        broadcast_iterator<S, L> end(const S& shape) noexcept;

        template <class S, layout_type L = DL>
        reverse_broadcast_iterator<S, L> rbegin(const S& shape) noexcept;
        template <class S, layout_type L = DL>
        reverse_broadcast_iterator<S, L> rend(const S& shape) noexcept;

        storage_iterator storage_begin() noexcept;
        storage_iterator storage_end() noexcept;

        reverse_storage_iterator storage_rbegin() noexcept;
        reverse_storage_iterator storage_rend() noexcept;

    private:

        template <layout_type L>
        layout_iterator<L> get_begin(bool end_index) noexcept;
        template <layout_type L>
        layout_iterator<L> get_end(bool end_index) noexcept;

        template <class S, layout_type L>
        broadcast_iterator<S, L> get_begin(const S& shape, bool end_index) noexcept;
        template <class S, layout_type L>
        broadcast_iterator<S, L> get_end(const S& shape, bool end_index) noexcept;

        template <class S>
        stepper get_stepper_begin(const S& shape) noexcept;
        template <class S>
        stepper get_stepper_end(const S& shape, layout_type l) noexcept;

        template <class S>
        const_stepper get_stepper_begin(const S& shape) const noexcept;
        template <class S>
        const_stepper get_stepper_end(const S& shape, layout_type l) const noexcept;

        derived_type& derived_cast();
    };

    template <class T>
    struct xcontainer_inner_types;

    template <class D>
    class xcontiguous_iterable : public xiterable<D>
    {
    public:

        using derived_type = D;

        using inner_types = xcontainer_inner_types<D>;
        using storage_type = typename inner_types::storage_type;
        // using allocator_type = allocator_type_t<std::decay_t<storage_type>>;
        using value_type = typename storage_type::value_type;
        using reference = std::conditional_t<std::is_const<storage_type>::value,
                                             typename storage_type::const_reference,
                                             typename storage_type::reference>;
        using const_reference = typename storage_type::const_reference;
        using pointer = typename storage_type::pointer;
        using const_pointer = typename storage_type::const_pointer;
        using size_type = typename storage_type::size_type;
        using difference_type = typename storage_type::difference_type;
        using simd_value_type = xsimd::simd_type<value_type>;

        using shape_type = typename inner_types::shape_type;
        using strides_type = typename inner_types::strides_type;
        using backstrides_type = typename inner_types::backstrides_type;

        using inner_shape_type = typename inner_types::inner_shape_type;
        using inner_strides_type = typename inner_types::inner_strides_type;
        using inner_backstrides_type = typename inner_types::inner_backstrides_type;

        using iterable_base = xiterable<D>;
        using stepper = typename iterable_base::stepper;
        using const_stepper = typename iterable_base::const_stepper;

        static constexpr layout_type static_layout = inner_types::layout;
        static constexpr bool contiguous_layout = static_layout != layout_type::dynamic;
        using data_alignment = xsimd::container_alignment_t<storage_type>;
        using simd_type = xsimd::simd_type<value_type>;


#if defined(_MSC_VER) && _MSC_VER >= 1910
        // Workaround for compiler bug in Visual Studio 2017 with respect to alias templates with non-type parameters.
        template <layout_type L>
        using layout_iterator = xiterator<typename iterable_base::stepper, typename iterable_base::inner_shape_type*, L>;
        template <layout_type L>
        using const_layout_iterator = xiterator<typename iterable_base::const_stepper, typename iterable_base::inner_shape_type*, L>;
        template <layout_type L>
        using reverse_layout_iterator = std::reverse_iterator<layout_iterator<L>>;
        template <layout_type L>
        using const_reverse_layout_iterator = std::reverse_iterator<const_layout_iterator<L>>;
#else
        template <layout_type L>
        using layout_iterator = typename iterable_base::template layout_iterator<L>;
        template <layout_type L>
        using const_layout_iterator = typename iterable_base::template const_layout_iterator<L>;
        template <layout_type L>
        using reverse_layout_iterator = typename iterable_base::template reverse_layout_iterator<L>;
        template <layout_type L>
        using const_reverse_layout_iterator = typename iterable_base::template const_reverse_layout_iterator<L>;
#endif

        template <class S, layout_type L>
        using broadcast_iterator = typename iterable_base::template broadcast_iterator<S, L>;
        template <class S, layout_type L>
        using const_broadcast_iterator = typename iterable_base::template const_broadcast_iterator<S, L>;
        template <class S, layout_type L>
        using reverse_broadcast_iterator = typename iterable_base::template reverse_broadcast_iterator<S, L>;
        template <class S, layout_type L>
        using const_reverse_broadcast_iterator = typename iterable_base::template const_reverse_broadcast_iterator<S, L>;

        using storage_iterator = typename storage_type::iterator;
        using const_storage_iterator = typename storage_type::const_iterator;
        using reverse_storage_iterator = typename storage_type::reverse_iterator;
        using const_reverse_storage_iterator = typename storage_type::const_reverse_iterator;

        template <layout_type L, class It1, class It2>
        using select_iterator_impl = std::conditional_t<L == static_layout, It1, It2>;

        template <layout_type L>
        using select_iterator = select_iterator_impl<L, storage_iterator, layout_iterator<L>>;
        template <layout_type L>
        using select_const_iterator = select_iterator_impl<L, const_storage_iterator, const_layout_iterator<L>>;
        template <layout_type L>
        using select_reverse_iterator = select_iterator_impl<L, reverse_storage_iterator, reverse_layout_iterator<L>>;
        template <layout_type L>
        using select_const_reverse_iterator = select_iterator_impl<L, const_reverse_storage_iterator, const_reverse_layout_iterator<L>>;

        using iterator = select_iterator<DL>;
        using const_iterator = select_const_iterator<DL>;
        using reverse_iterator = select_reverse_iterator<DL>;
        using const_reverse_iterator = select_const_reverse_iterator<DL>;

        template <layout_type L = DL>
        select_iterator<L> begin() noexcept;
        template <layout_type L = DL>
        select_iterator<L> end() noexcept;

        template <layout_type L = DL>
        select_const_iterator<L> begin() const noexcept;
        template <layout_type L = DL>
        select_const_iterator<L> end() const noexcept;
        template <layout_type L = DL>
        select_const_iterator<L> cbegin() const noexcept;
        template <layout_type L = DL>
        select_const_iterator<L> cend() const noexcept;

        template <layout_type L = DL>
        select_reverse_iterator<L> rbegin() noexcept;
        template <layout_type L = DL>
        select_reverse_iterator<L> rend() noexcept;

        template <layout_type L = DL>
        select_const_reverse_iterator<L> rbegin() const noexcept;
        template <layout_type L = DL>
        select_const_reverse_iterator<L> rend() const noexcept;
        template <layout_type L = DL>
        select_const_reverse_iterator<L> crbegin() const noexcept;
        template <layout_type L = DL>
        select_const_reverse_iterator<L> crend() const noexcept;

        template <class S, layout_type L = DL>
        broadcast_iterator<S, L> begin(const S& shape) noexcept;
        template <class S, layout_type L = DL>
        broadcast_iterator<S, L> end(const S& shape) noexcept;

        template <class S, layout_type L = DL>
        const_broadcast_iterator<S, L> begin(const S& shape) const noexcept;
        template <class S, layout_type L = DL>
        const_broadcast_iterator<S, L> end(const S& shape) const noexcept;
        template <class S, layout_type L = DL>
        const_broadcast_iterator<S, L> cbegin(const S& shape) const noexcept;
        template <class S, layout_type L = DL>
        const_broadcast_iterator<S, L> cend(const S& shape) const noexcept;

        template <class S, layout_type L = DL>
        reverse_broadcast_iterator<S, L> rbegin(const S& shape) noexcept;
        template <class S, layout_type L = DL>
        reverse_broadcast_iterator<S, L> rend(const S& shape) noexcept;

        template <class S, layout_type L = DL>
        const_reverse_broadcast_iterator<S, L> rbegin(const S& shape) const noexcept;
        template <class S, layout_type L = DL>
        const_reverse_broadcast_iterator<S, L> rend(const S& shape) const noexcept;
        template <class S, layout_type L = DL>
        const_reverse_broadcast_iterator<S, L> crbegin(const S& shape) const noexcept;
        template <class S, layout_type L = DL>
        const_reverse_broadcast_iterator<S, L> crend(const S& shape) const noexcept;

    private:

        derived_type& derived_cast();
        const derived_type& derived_cast() const;
    };

#undef DL

    /**********************************
     * xconst_iterable implementation *
     **********************************/

    /**
     * @name Constant iterators
     */
    //@{
    /**
     * Returns a constant iterator to the first element of the expression.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <layout_type L>
    inline auto xconst_iterable<D>::begin() const noexcept -> const_layout_iterator<L>
    {
        return this->template cbegin<L>();
    }

    /**
     * Returns a constant iterator to the element following the last element
     * of the expression.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <layout_type L>
    inline auto xconst_iterable<D>::end() const noexcept -> const_layout_iterator<L>
    {
        return this->template cend<L>();
    }

    /**
     * Returns a constant iterator to the first element of the expression.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <layout_type L>
    inline auto xconst_iterable<D>::cbegin() const noexcept -> const_layout_iterator<L>
    {
        return this->template get_cbegin<L>(false);
    }

    /**
     * Returns a constant iterator to the element following the last element
     * of the expression.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <layout_type L>
    inline auto xconst_iterable<D>::cend() const noexcept -> const_layout_iterator<L>
    {
        return this->template get_cend<L>(true);
    }
    //@}

    /**
     * @name Constant reverse iterators
     */
    //@{
    /**
     * Returns a constant iterator to the first element of the reversed expression.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <layout_type L>
    inline auto xconst_iterable<D>::rbegin() const noexcept -> const_reverse_layout_iterator<L>
    {
        return this->template crbegin<L>();
    }

    /**
     * Returns a constant iterator to the element following the last element
     * of the reversed expression.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <layout_type L>
    inline auto xconst_iterable<D>::rend() const noexcept -> const_reverse_layout_iterator<L>
    {
        return this->template crend<L>();
    }

    /**
     * Returns a constant iterator to the first element of the reversed expression.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <layout_type L>
    inline auto xconst_iterable<D>::crbegin() const noexcept -> const_reverse_layout_iterator<L>
    {
        return const_reverse_layout_iterator<L>(get_cend<L>(true));
    }

    /**
     * Returns a constant iterator to the element following the last element
     * of the reversed expression.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <layout_type L>
    inline auto xconst_iterable<D>::crend() const noexcept -> const_reverse_layout_iterator<L>
    {
        return const_reverse_layout_iterator<L>(get_cbegin<L>(false));
    }
    //@}

    /**
     * @name Constant broadcast iterators
     */
    //@{
    /**
     * Returns a constant iterator to the first element of the expression. The
     * iteration is broadcasted to the specified shape.
     * @param shape the shape used for broadcasting
     * @tparam S type of the \c shape parameter.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <class S, layout_type L>
    inline auto xconst_iterable<D>::begin(const S& shape) const noexcept -> const_broadcast_iterator<S, L>
    {
        return cbegin<S, L>(shape);
    }

    /**
     * Returns a constant iterator to the element following the last element of the
     * expression. The iteration is broadcasted to the specified shape.
     * @param shape the shape used for broadcasting
     * @tparam S type of the \c shape parameter.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <class S, layout_type L>
    inline auto xconst_iterable<D>::end(const S& shape) const noexcept -> const_broadcast_iterator<S, L>
    {
        return cend<S, L>(shape);
    }

    /**
     * Returns a constant iterator to the first element of the expression. The
     * iteration is broadcasted to the specified shape.
     * @param shape the shape used for broadcasting
     * @tparam S type of the \c shape parameter.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <class S, layout_type L>
    inline auto xconst_iterable<D>::cbegin(const S& shape) const noexcept -> const_broadcast_iterator<S, L>
    {
        return get_cbegin<S, L>(shape, false);
    }

    /**
     * Returns a constant iterator to the element following the last element of the
     * expression. The iteration is broadcasted to the specified shape.
     * @param shape the shape used for broadcasting
     * @tparam S type of the \c shape parameter.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <class S, layout_type L>
    inline auto xconst_iterable<D>::cend(const S& shape) const noexcept -> const_broadcast_iterator<S, L>
    {
        return get_cend<S, L>(shape, true);
    }
    //@}

    /**
     * @name Constant reverse broadcast iterators
     */
    //@{
    /**
     * Returns a constant iterator to the first element of the reversed expression.
     * The iteration is broadcasted to the specified shape.
     * @param shape the shape used for broadcasting
     * @tparam S type of the \c shape parameter.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <class S, layout_type L>
    inline auto xconst_iterable<D>::rbegin(const S& shape) const noexcept -> const_reverse_broadcast_iterator<S, L>
    {
        return crbegin<S, L>(shape);
    }

    /**
     * Returns a constant iterator to the element following the last element of the
     * reversed expression. The iteration is broadcasted to the specified shape.
     * @param shape the shape used for broadcasting
     * @tparam S type of the \c shape parameter.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <class S, layout_type L>
    inline auto xconst_iterable<D>::rend(const S& shape) const noexcept -> const_reverse_broadcast_iterator<S, L>
    {
        return crend<S, L>(shape);
    }

    /**
     * Returns a constant iterator to the first element of the reversed expression.
     * The iteration is broadcasted to the specified shape.
     * @param shape the shape used for broadcasting
     * @tparam S type of the \c shape parameter.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <class S, layout_type L>
    inline auto xconst_iterable<D>::crbegin(const S& shape) const noexcept -> const_reverse_broadcast_iterator<S, L>
    {
        return const_reverse_broadcast_iterator<S, L>(get_cend<S, L>(shape, true));
    }

    /**
     * Returns a constant iterator to the element following the last element of the
     * reversed expression. The iteration is broadcasted to the specified shape.
     * @param shape the shape used for broadcasting
     * @tparam S type of the \c shape parameter.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <class S, layout_type L>
    inline auto xconst_iterable<D>::crend(const S& shape) const noexcept -> const_reverse_broadcast_iterator<S, L>
    {
        return const_reverse_broadcast_iterator<S, L>(get_cbegin<S, L>(shape, false));
    }
    //@}

    template <class D>
    inline auto xconst_iterable<D>::storage_begin() const noexcept -> const_storage_iterator
    {
        return this->template cbegin<XTENSOR_DEFAULT_LAYOUT>();
    }

    template <class D>
    inline auto xconst_iterable<D>::storage_end() const noexcept -> const_storage_iterator
    {
        return this->template cend<XTENSOR_DEFAULT_LAYOUT>();
    }

    template <class D>
    inline auto xconst_iterable<D>::storage_cbegin() const noexcept -> const_storage_iterator
    {
        return this->template cbegin<XTENSOR_DEFAULT_LAYOUT>();
    }

    template <class D>
    inline auto xconst_iterable<D>::storage_cend() const noexcept -> const_storage_iterator
    {
        return this->template cend<XTENSOR_DEFAULT_LAYOUT>();
    }

    template <class D>
    inline auto xconst_iterable<D>::storage_rbegin() const noexcept -> const_reverse_storage_iterator
    {
        return this->template crbegin<XTENSOR_DEFAULT_LAYOUT>();
    }

    template <class D>
    inline auto xconst_iterable<D>::storage_rend() const noexcept -> const_reverse_storage_iterator
    {
        return this->template crend<XTENSOR_DEFAULT_LAYOUT>();
    }

    template <class D>
    inline auto xconst_iterable<D>::storage_crbegin() const noexcept -> const_reverse_storage_iterator
    {
        return this->template crbegin<XTENSOR_DEFAULT_LAYOUT>();
    }

    template <class D>
    inline auto xconst_iterable<D>::storage_crend() const noexcept -> const_reverse_storage_iterator
    {
        return this->template crend<XTENSOR_DEFAULT_LAYOUT>();
    }

    template <class D>
    template <layout_type L>
    inline auto xconst_iterable<D>::get_cbegin(bool end_index) const noexcept -> const_layout_iterator<L>
    {
        return const_layout_iterator<L>(get_stepper_begin(get_shape()), &get_shape(), end_index);
    }

    template <class D>
    template <layout_type L>
    inline auto xconst_iterable<D>::get_cend(bool end_index) const noexcept -> const_layout_iterator<L>
    {
        return const_layout_iterator<L>(get_stepper_end(get_shape(), L), &get_shape(), end_index);
    }

    template <class D>
    template <class S, layout_type L>
    inline auto xconst_iterable<D>::get_cbegin(const S& shape, bool end_index) const noexcept -> const_broadcast_iterator<S, L>
    {
        return const_broadcast_iterator<S, L>(get_stepper_begin(shape), shape, end_index);
    }

    template <class D>
    template <class S, layout_type L>
    inline auto xconst_iterable<D>::get_cend(const S& shape, bool end_index) const noexcept -> const_broadcast_iterator<S, L>
    {
        return const_broadcast_iterator<S, L>(get_stepper_end(shape, L), shape, end_index);
    }

    template <class D>
    template <class S>
    inline auto xconst_iterable<D>::get_stepper_begin(const S& shape) const noexcept -> const_stepper
    {
        return derived_cast().stepper_begin(shape);
    }

    template <class D>
    template <class S>
    inline auto xconst_iterable<D>::get_stepper_end(const S& shape, layout_type l) const noexcept -> const_stepper
    {
        return derived_cast().stepper_end(shape, l);
    }

    template <class D>
    inline auto xconst_iterable<D>::get_shape() const -> const inner_shape_type&
    {
        return derived_cast().shape();
    }

    template <class D>
    inline auto xconst_iterable<D>::derived_cast() const -> const derived_type&
    {
        return *static_cast<const derived_type*>(this);
    }

    /****************************
     * xiterable implementation *
     ****************************/

    /**
     * @name Iterators
     */
    //@{
    /**
     * Returns an iterator to the first element of the expression.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <layout_type L>
    inline auto xiterable<D>::begin() noexcept -> layout_iterator<L>
    {
        return get_begin<L>(false);
    }

    /**
     * Returns an iterator to the element following the last element
     * of the expression.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <layout_type L>
    inline auto xiterable<D>::end() noexcept -> layout_iterator<L>
    {
        return get_end<L>(true);
    }
    //@}

    /**
     * @name Reverse iterators
     */
    //@{
    /**
     * Returns an iterator to the first element of the reversed expression.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <layout_type L>
    inline auto xiterable<D>::rbegin() noexcept -> reverse_layout_iterator<L>
    {
        return reverse_layout_iterator<L>(get_end<L>(true));
    }

    /**
     * Returns an iterator to the element following the last element
     * of the reversed expression.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <layout_type L>
    inline auto xiterable<D>::rend() noexcept -> reverse_layout_iterator<L>
    {
        return reverse_layout_iterator<L>(get_begin<L>(false));
    }
    //@}

    /**
     * @name Broadcast iterators
     */
    //@{
    /**
     * Returns an iterator to the first element of the expression. The
     * iteration is broadcasted to the specified shape.
     * @param shape the shape used for broadcasting
     * @tparam S type of the \c shape parameter.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <class S, layout_type L>
    inline auto xiterable<D>::begin(const S& shape) noexcept -> broadcast_iterator<S, L>
    {
        return get_begin<S, L>(shape, false);
    }

    /**
     * Returns an iterator to the element following the last element of the
     * expression. The iteration is broadcasted to the specified shape.
     * @param shape the shape used for broadcasting
     * @tparam S type of the \c shape parameter.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <class S, layout_type L>
    inline auto xiterable<D>::end(const S& shape) noexcept -> broadcast_iterator<S, L>
    {
        return get_end<S, L>(shape, true);
    }
    //@}

    /**
     * @name Reverse broadcast iterators
     */
    //@{
    /**
     * Returns an iterator to the first element of the reversed expression. The
     * iteration is broadcasted to the specified shape.
     * @param shape the shape used for broadcasting
     * @tparam S type of the \c shape parameter.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <class S, layout_type L>
    inline auto xiterable<D>::rbegin(const S& shape) noexcept -> reverse_broadcast_iterator<S, L>
    {
        return reverse_broadcast_iterator<S, L>(get_end<S, L>(shape, true));
    }

    /**
     * Returns an iterator to the element following the last element of the
     * reversed expression. The iteration is broadcasted to the specified shape.
     * @param shape the shape used for broadcasting
     * @tparam S type of the \c shape parameter.
     * @tparam L layout used for the traversal. Default value is \c XTENSOR_DEFAULT_LAYOUT.
     */
    template <class D>
    template <class S, layout_type L>
    inline auto xiterable<D>::rend(const S& shape) noexcept -> reverse_broadcast_iterator<S, L>
    {
        return reverse_broadcast_iterator<S, L>(get_begin<S, L>(shape, false));
    }
    //@}

    template <class D>
    inline auto xiterable<D>::storage_begin() noexcept -> storage_iterator
    {
        return this->template begin<XTENSOR_DEFAULT_LAYOUT>();
    }

    template <class D>
    inline auto xiterable<D>::storage_end() noexcept -> storage_iterator
    {
        return this->template end<XTENSOR_DEFAULT_LAYOUT>();
    }

    template <class D>
    inline auto xiterable<D>::storage_rbegin() noexcept -> reverse_storage_iterator
    {
        return this->template rbegin<XTENSOR_DEFAULT_LAYOUT>();
    }

    template <class D>
    inline auto xiterable<D>::storage_rend() noexcept -> reverse_storage_iterator
    {
        return this->template rend<XTENSOR_DEFAULT_LAYOUT>();
    }

    template <class D>
    template <layout_type L>
    inline auto xiterable<D>::get_begin(bool end_index) noexcept -> layout_iterator<L>
    {
        return layout_iterator<L>(get_stepper_begin(this->get_shape()), &(this->get_shape()), end_index);
    }

    template <class D>
    template <layout_type L>
    inline auto xiterable<D>::get_end(bool end_index) noexcept -> layout_iterator<L>
    {
        return layout_iterator<L>(get_stepper_end(this->get_shape(), L), &(this->get_shape()), end_index);
    }

    template <class D>
    template <class S, layout_type L>
    inline auto xiterable<D>::get_begin(const S& shape, bool end_index) noexcept -> broadcast_iterator<S, L>
    {
        return broadcast_iterator<S, L>(get_stepper_begin(shape), shape, end_index);
    }

    template <class D>
    template <class S, layout_type L>
    inline auto xiterable<D>::get_end(const S& shape, bool end_index) noexcept -> broadcast_iterator<S, L>
    {
        return broadcast_iterator<S, L>(get_stepper_end(shape, L), shape, end_index);
    }

    template <class D>
    template <class S>
    inline auto xiterable<D>::get_stepper_begin(const S& shape) noexcept -> stepper
    {
        return derived_cast().stepper_begin(shape);
    }

    template <class D>
    template <class S>
    inline auto xiterable<D>::get_stepper_end(const S& shape, layout_type l) noexcept -> stepper
    {
        return derived_cast().stepper_end(shape, l);
    }

    template <class D>
    template <class S>
    inline auto xiterable<D>::get_stepper_begin(const S& shape) const noexcept -> const_stepper
    {
        return derived_cast().stepper_begin(shape);
    }

    template <class D>
    template <class S>
    inline auto xiterable<D>::get_stepper_end(const S& shape, layout_type l) const noexcept -> const_stepper
    {
        return derived_cast().stepper_end(shape, l);
    }

    template <class D>
    inline auto xiterable<D>::derived_cast() -> derived_type&
    {
        return *static_cast<derived_type*>(this);
    }

    /****************************
     * xcontiguous iterator api *
     ****************************/

    template <class D>
    template <layout_type L>
    inline auto xcontiguous_iterable<D>::begin() noexcept -> select_iterator<L>
    {
        return xtl::mpl::static_if<L == static_layout>([&](auto self)
        {
            return self(*this).derived_cast().storage_begin();
        }, /*else*/ [&](auto self)
        {
            return self(*this).iterable_base::template begin<L>();
        });
    }

    template <class D>
    template <layout_type L>
    inline auto xcontiguous_iterable<D>::end() noexcept -> select_iterator<L>
    {
        return xtl::mpl::static_if<L == static_layout>([&](auto self)
        {
            return self(*this).derived_cast().storage_end();
        }, /*else*/ [&](auto self)
        {
            return self(*this).iterable_base::template end<L>();
        });
    }

    template <class D>
    template <layout_type L>
    inline auto xcontiguous_iterable<D>::begin() const noexcept -> select_const_iterator<L>
    {
        return this->template cbegin<L>();
    }

    template <class D>
    template <layout_type L>
    inline auto xcontiguous_iterable<D>::end() const noexcept -> select_const_iterator<L>
    {
        return this->template cend<L>();
    }

    template <class D>
    template <layout_type L>
    inline auto xcontiguous_iterable<D>::cbegin() const noexcept -> select_const_iterator<L>
    {
        return xtl::mpl::static_if<L == static_layout>([&](auto self)
        {
            return self(*this).derived_cast().storage_cbegin();
        }, /*else*/ [&](auto self)
        {
            return self(*this).iterable_base::template cbegin<L>();
        });
    }

    template <class D>
    template <layout_type L>
    inline auto xcontiguous_iterable<D>::cend() const noexcept -> select_const_iterator<L>
    {
        return xtl::mpl::static_if<L == static_layout>([&](auto self)
        {
            return self(*this).derived_cast().storage_cend();
        }, /*else*/ [&](auto self)
        {
            return self(*this).iterable_base::template cend<L>();
        });
    }

    template <class D>
    template <layout_type L>
    inline auto xcontiguous_iterable<D>::rbegin() noexcept -> select_reverse_iterator<L>
    {
        return xtl::mpl::static_if<L == static_layout>([&](auto self)
        {
            return self(*this).derived_cast().storage_rbegin();
        }, /*else*/ [&](auto self)
        {
            return self(*this).iterable_base::template rbegin<L>();
        });
    }

    template <class D>
    template <layout_type L>
    inline auto xcontiguous_iterable<D>::rend() noexcept -> select_reverse_iterator<L>
    {
        return xtl::mpl::static_if<L == static_layout>([&](auto self)
        {
            return self(*this).derived_cast().storage_rend();
        }, /*else*/ [&](auto self)
        {
            return self(*this).iterable_base::template rend<L>();
        });
    }

    template <class D>
    template <layout_type L>
    inline auto xcontiguous_iterable<D>::rbegin() const noexcept -> select_const_reverse_iterator<L>
    {
        return this->template crbegin<L>();
    }

    template <class D>
    template <layout_type L>
    inline auto xcontiguous_iterable<D>::rend() const noexcept -> select_const_reverse_iterator<L>
    {
        return this->template crend<L>();
    }

    template <class D>
    template <layout_type L>
    inline auto xcontiguous_iterable<D>::crbegin() const noexcept -> select_const_reverse_iterator<L>
    {
        return xtl::mpl::static_if<L == static_layout>([&](auto self)
        {
            return self(*this).derived_cast().storage_crbegin();
        }, /*else*/ [&](auto self)
        {
            return self(*this).iterable_base::template crbegin<L>();
        });
    }

    template <class D>
    template <layout_type L>
    inline auto xcontiguous_iterable<D>::crend() const noexcept -> select_const_reverse_iterator<L>
    {
        return xtl::mpl::static_if<L == static_layout>([&](auto self)
        {
            return self(*this).derived_cast().storage_crend();
        }, /*else*/ [&](auto self)
        {
            return self(*this).iterable_base::template crend<L>();
        });
    }

    /*****************************
     * Broadcasting iterator api *
     *****************************/

    template <class D>
    template <class S, layout_type L>
    inline auto xcontiguous_iterable<D>::begin(const S& shape) noexcept -> broadcast_iterator<S, L>
    {
        return iterable_base::template begin<S, L>(shape);
    }

    template <class D>
    template <class S, layout_type L>
    inline auto xcontiguous_iterable<D>::end(const S& shape) noexcept -> broadcast_iterator<S, L>
    {
        return iterable_base::template end<S, L>(shape);
    }

    template <class D>
    template <class S, layout_type L>
    inline auto xcontiguous_iterable<D>::begin(const S& shape) const noexcept -> const_broadcast_iterator<S, L>
    {
        return iterable_base::template begin<S, L>(shape);
    }

    template <class D>
    template <class S, layout_type L>
    inline auto xcontiguous_iterable<D>::end(const S& shape) const noexcept -> const_broadcast_iterator<S, L>
    {
        return iterable_base::template end<S, L>(shape);
    }

    template <class D>
    template <class S, layout_type L>
    inline auto xcontiguous_iterable<D>::cbegin(const S& shape) const noexcept -> const_broadcast_iterator<S, L>
    {
        return iterable_base::template cbegin<S, L>(shape);
    }

    template <class D>
    template <class S, layout_type L>
    inline auto xcontiguous_iterable<D>::cend(const S& shape) const noexcept -> const_broadcast_iterator<S, L>
    {
        return iterable_base::template cend<S, L>(shape);
    }

    template <class D>
    template <class S, layout_type L>
    inline auto xcontiguous_iterable<D>::rbegin(const S& shape) noexcept -> reverse_broadcast_iterator<S, L>
    {
        return iterable_base::template rbegin<S, L>(shape);
    }

    template <class D>
    template <class S, layout_type L>
    inline auto xcontiguous_iterable<D>::rend(const S& shape) noexcept -> reverse_broadcast_iterator<S, L>
    {
        return iterable_base::template rend<S, L>(shape);
    }

    template <class D>
    template <class S, layout_type L>
    inline auto xcontiguous_iterable<D>::rbegin(const S& shape) const noexcept -> const_reverse_broadcast_iterator<S, L>
    {
        return iterable_base::template rbegin<S, L>(shape);
    }

    template <class D>
    template <class S, layout_type L>
    inline auto xcontiguous_iterable<D>::rend(const S& shape) const noexcept -> const_reverse_broadcast_iterator<S, L>
    {
        return iterable_base::template rend<S, L>(shape);
    }

    template <class D>
    template <class S, layout_type L>
    inline auto xcontiguous_iterable<D>::crbegin(const S& shape) const noexcept -> const_reverse_broadcast_iterator<S, L>
    {
        return iterable_base::template crbegin<S, L>(shape);
    }

    template <class D>
    template <class S, layout_type L>
    inline auto xcontiguous_iterable<D>::crend(const S& shape) const noexcept -> const_reverse_broadcast_iterator<S, L>
    {
        return iterable_base::template crend<S, L>(shape);
    }

    template <class D>
    inline auto xcontiguous_iterable<D>::derived_cast() -> derived_type&
    {
        return *static_cast<derived_type*>(this);
    }

    template <class D>
    inline auto xcontiguous_iterable<D>::derived_cast() const -> const derived_type&
    {
        return *static_cast<const derived_type*>(this);
    }

}

#endif
